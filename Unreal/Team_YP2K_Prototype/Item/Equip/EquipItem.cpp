#include "Item/Equip/EquipItem.h"
#include "../../Player/MyPlayer.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AEquipItem::AEquipItem()
{
    PrimaryActorTick.bCanEverTick = true;

    _Type = ItemType::Equipment;

    _trigger->SetSphereRadius(100.0f);
    _trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void AEquipItem::BeginPlay()
{
    Super::BeginPlay();
    _trigger->OnComponentBeginOverlap.AddDynamic(this, &AEquipItem::OnOverlapBegin);
}

// Called every frame
void AEquipItem::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEquipItem::EquipPlayer(class AMyPlayer *Player)
{
    if (Player == nullptr)
        return;

    if (_equipItem)
    {
        switch (_equipItemType)
        {
        case EItemType::UpperArmor:
            Player->GetMesh()->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::LowerArmor:
            Player->_lowerBodyMesh->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::ShoulderArmor:
            Player->_shoulderBodyMesh->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::Sword:
            Player->_swordBodyMesh->SetSkeletalMesh(_equipItem);
            break;
        case EItemType::Shield:
            Player->_shieldBodyMesh->SetSkeletalMesh(_equipItem);
            break;
        default:
            break;
        }
    }
}

void AEquipItem::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
    auto Player = Cast<AMyPlayer>(OtherActor);
    if (Player)
    {
        EquipPlayer(Player);
        Player->ItemEquipped.Broadcast(this);
        Destroy();
       // _meshComponent->SetVisibility(false);
        //_meshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    }
}
