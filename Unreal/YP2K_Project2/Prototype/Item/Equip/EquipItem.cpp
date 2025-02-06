#include "Item/Equip/EquipItem.h"
#include "Base/MyGameInstance.h"
#include "Item/BaseItem.h"
#include "../../Player/MyPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Component/StatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEquipItem::AEquipItem()
{
    PrimaryActorTick.bCanEverTick = true;

    _Type = ItemType::Equipment;

    _trigger->SetSphereRadius(100.0f);
    _trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AEquipItem::SetItemWithCode(int32 itemCode)
{
    auto gameinstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
    if (gameinstance != nullptr)
    {
        FItemData *data = gameinstance->GetEquipItemData(itemCode);
        if (data == nullptr || data->_Name == TEXT(""))
        {
            return;
        }

        _Code = data->_Code;
        _Texture = data->_Texture;
        _Mesh = data->_Mesh;
        _equipItem = data->_Skeletal;
        _Value = data->_Value;
        _Price = data->_Price;
        _Name = data->_Name;
        _Type = data->_Type;
        _ModStatType = data->_ModTarget;
        _Description = data->_Description;
        _Equip = data->_Equip;

        _meshComponent->SetStaticMesh(_Mesh);
    }
}

void AEquipItem::SetEquipType(int num)
{
    if (num >= 0 && num < static_cast<int32>(EItemType::Shield) + 1)
    {
        _equipItemType = static_cast<EItemType>(num);

        FString EnumValueAsString = UEnum::GetValueAsString(_equipItemType);
    }
    else
    {
        _equipItemType = EItemType::Helmet;

        FString EnumValueAsString = UEnum::GetValueAsString(_equipItemType);
    }
}

// Called when the game starts or when spawned
void AEquipItem::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AEquipItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEquipItem::EquipPlayer()
{
    if (_player == nullptr)
    {
        return;
    }

    if (_equipItem)
    {
        switch (_equipItemType)
        {
        case EItemType::UpperArmor:
            _player->GetMesh()->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::LowerArmor:
            _player->GetLowerBodyMesh()->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::ShoulderArmor:
            _player->GetShoulderBodyMesh()->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::Sword:
            _player->GetSwordBodyMesh()->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::Shield:
            _player->GetShieldBodyMesh()->SetSkeletalMesh(_equipItem);
            break;
        default:
            break;
        }
    }
    _isEquipped = true;
}

void AEquipItem::UnEquip()
{
    if (_player == nullptr)
    {
        APlayerController *playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (playerController)
        {
            AMyPlayer *currentPlayer = Cast<AMyPlayer>(playerController->GetPawn());
            if (currentPlayer)
                _player = currentPlayer;
            else
                return;
        }
    }

    switch (_equipItemType)
    {
    case EItemType::UpperArmor:
        _player->EquipBaseBody();
        break;
    case EItemType::LowerArmor:
        _player->EquipBaseLower();
        break;
    case EItemType::ShoulderArmor:
        _player->EquipBaseShoulder();
        break;
    case EItemType::Sword:
        _player->GetSwordBodyMesh()->SetSkeletalMesh(nullptr);
        break;
    case EItemType::Shield:
        _player->GetShieldBodyMesh()->SetSkeletalMesh(nullptr);
        break;
    default:
        break;
    }

    _player->GetStatComponent()->DropItem(this);
    _isEquipped = false;
}

void AEquipItem::UseItem()
{
    if (!_player)
        SetPlayer();

    EquipPlayer();
    _player->ItemEquipped.Broadcast(this);

    _player->GetStatComponent()->UseItem(this);
}

void AEquipItem::DropItem(FVector location, FRotator rotation)
{
    Super::DropItem(location, rotation);

    if (_isEquipped)
        UnEquip();
}
