// Fill out your copyright notice in the Description page of Project Settings.



#include "Item/BaseItem.h"

#include "Player/MyPlayer.h"

#include "Base/MyGameInstance.h"
#include "Component/InventoryComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABaseItem::ABaseItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

	//Setting Default Mesh and Texture
	// static ConstructorHelpers::FObjectFinder<UStaticMesh> defaultMesh(
	// 	TEXT("/Script/Engine.StaticMesh'/Game/Kobo_Dungeon/Meshes/SM-Pottery-04.SM-Pottery-04'")
	// );
	// if (defaultMesh.Succeeded())
	// {
	// 	_meshComponent->SetStaticMesh(defaultMesh.Object);
	// }
	// static ConstructorHelpers::FObjectFinder<UTexture2D> defaultTexture(
	// 	TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/Tex_container_03_b.Tex_container_03_b'")
	// );
	// if (defaultTexture.Succeeded())
	// {
	// 	_Texture = defaultTexture.Object;
	// }

	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_trigger->SetSphereRadius(60.0f);

	_meshComponent->SetCollisionProfileName(TEXT("Item"));
	_trigger->SetCollisionProfileName(TEXT("Item"));
}

void ABaseItem::SetItemWithCode(int32 itemCode)
{
	auto gameinstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (gameinstance != nullptr)
	{
		FItemData* data = gameinstance->GetConsumeItemData(itemCode);
		if (data == nullptr || data->_Name == TEXT(""))
		{
			UE_LOG(LogTemp, Error, TEXT("Data Load Faild!"));
			return;
		}

		_Name = data->_Name;
		_Type = data->_Type;
		_Description = data->_Description;
		_Price = data->_Price;
		_Value = data->_Value;
		_Mesh = data->_Mesh;
		_Texture = data->_Texture;

		_meshComponent->SetStaticMesh(_Mesh);
	}
}

void ABaseItem::Init()
{
	_meshComponent->SetStaticMesh(_Mesh);

	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseItem::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
 void ABaseItem::BeginPlay()
 {
	Super::BeginPlay();
 }

 void ABaseItem::PostInitializeComponents()
 {
	 Super::PostInitializeComponents();

	 _trigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnMyCharacterOverlap);
	 _trigger->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnMyCharacterOverlapEnd);
 }

// Called every frame
void ABaseItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ABaseItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_player = Cast<AMyPlayer>(OverlappedComponent);
	if (_player == nullptr)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Player Collision!"));
	_player->GetItem(this);
	Disable();
}

void ABaseItem::OnMyCharacterOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseItem::GetItem()
{

}

void ABaseItem::UseItem()
{
}

void ABaseItem::DropItem(FVector location, FRotator rotation)
{
	SetActorLocationAndRotation(location, rotation);
	Init();
}
