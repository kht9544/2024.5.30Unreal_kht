// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyCharacter.h"
#include "MonsterCharacter.h"

// Sets default values
AMyItem::AMyItem()
{
	PrimaryActorTick.bCanEverTick = false;

	_meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> sm
	(TEXT("/Script/Engine.StaticMesh'/Game/Weapon_Pack/Mesh/Weapons/Weapons_Kit/SM_Axe.SM_Axe'"));


	if (sm.Succeeded())
	{
		_meshComponent->SetStaticMesh(sm.Object);
	}

	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_meshComponent->SetCollisionProfileName(TEXT("MyItem"));
	_trigger->SetCollisionProfileName(TEXT("MyItem"));
	_trigger->SetSphereRadius(60.0f);
}

// Called when the game starts or when spawned
void AMyItem::BeginPlay()
{
	Super::BeginPlay();

	Init();
}


void AMyItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	CanPlayerPick = true;
	auto myCharacter = Cast<AMyCharacter>(OtherActor);
	OverlappingCharacter = Cast<AMyCharacter>(OtherActor);
	if (myCharacter)
	{
		if (myCharacter->CanPickItem)
		{
			myCharacter->AddAttackDamage(this, 50);
			myCharacter->AddItem(this);
			Disable();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Can't pick"));
		}
		//CanPlayerPick = true;
	}
	else
	{
		//CanPlayerPick = false;
	}
	CanPlayerPick = false;
	myCharacter->CanPickItem = false;
}

void AMyItem::Init()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AMyItem::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

}

void AMyItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnMyCharacterOverlap);
}


// Called every frame
void AMyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyItem::SetItemPos(FVector pos, FRotator rot)
{
	Init();

	SetActorLocation(pos);
	SetActorRotation(rot);
}

void AMyItem::PickUpItem()
{
	if (OverlappingCharacter && CanPlayerPick)
	{
		OverlappingCharacter->AddItem(this);
		Disable();
		OverlappingCharacter = nullptr; // Clear reference after picking up
		CanPlayerPick = false;
	}
}

