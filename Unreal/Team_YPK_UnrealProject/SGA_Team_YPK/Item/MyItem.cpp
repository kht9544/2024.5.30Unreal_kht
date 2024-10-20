// Fill out your copyright notice in the Description page of Project Settings.


#include "MyItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "MyPlayer.h"

AMyItem::AMyItem() : _itemId(-1)
{
	PrimaryActorTick.bCanEverTick = true;

	_meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	_trigger = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));


	_meshComponent->SetupAttachment(RootComponent);
	_trigger->SetupAttachment(_meshComponent);

	_meshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

	_meshComponent->SetCollisionProfileName(TEXT("Item"));
	_trigger->SetCollisionProfileName(TEXT("Item"));
	_trigger->SetSphereRadius(60.0f);

	_trigger->OnComponentBeginOverlap.AddDynamic(this, &AMyItem::OnMyCharacterOverlap);


}

void AMyItem::BeginPlay()
{
	Super::BeginPlay();

	Init();
	
}

void AMyItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
	auto myPlayer = Cast<AMyPlayer>(OtherActor);
	if (myPlayer)
	{
		myPlayer->AddAttackDamage(this, 50);
		Disable();
	}
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


