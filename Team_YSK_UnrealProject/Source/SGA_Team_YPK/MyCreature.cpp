// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCreature.h"
#include "MyStatComponent.h"
#include "MyInvenComponent.h"
#include "Engine/DamageEvents.h"
#include "MyHpBar.h"
#include "MyPlayer.h"
#include "Components/WidgetComponent.h"

//TODO : YSR Particle
#include "MyGameInstance.h"
#include "MyEffectManager.h"
//TODO : YSR Sound
#include "MySoundManager.h"

// Sets default values
AMyCreature::AMyCreature()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));

	_invenCom = CreateDefaultSubobject<UMyInvenComponent>(TEXT("Inven"));

}

// Called when the game starts or when spawned
void AMyCreature::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_statCom->SetLevelAndInit(1);


}

// Called every frame
void AMyCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMyCreature::Attackhit()
{
	TArray<FHitResult> hitResults;
FCollisionQueryParams params(NAME_None, false, this);

float attackRange = 500.0f;
float attackRadius = 50.0f;

bool bResult = GetWorld()->SweepMultiByChannel
(
	hitResults,
	GetActorLocation(),
	GetActorLocation() + GetActorForwardVector() * attackRange,
	FQuat::Identity,
	ECollisionChannel::ECC_GameTraceChannel2,
	FCollisionShape::MakeSphere(attackRadius),
	params
);

FVector vec = GetActorForwardVector() * attackRange;
FVector center = GetActorLocation() + vec * 0.5f;

FColor drawColor = FColor::Green;

if (bResult)
{
	drawColor = FColor::Red;

	for (auto& hitResult : hitResults)
	{
		if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
		{
			FDamageEvent DamageEvent;
			hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);

			// TODO : YSR Particle
			_hitPoint = hitResult.ImpactPoint;
			EffectManager->Play(*GetHitParticleName(), _hitPoint);
			SoundManager->PlaySound(*GetHitSoundName(), _hitPoint);
		}
	}
}
else
{
	FVector missLocation = GetActorLocation();
	SoundManager->PlaySound(*GetSwingSoundName(), missLocation);
}


}

//TODO : YSR Particle : Particle 이름
FString AMyCreature::GetHitParticleName() const
{
	return "default_hit_particle";
}

//TODO : YSR Sound
FString AMyCreature::GetHitSoundName() const
{
	return "default_hit_sound";
}

FString AMyCreature::GetSwingSoundName() const
{
	return "default_SwingAttackSound";
}

FString AMyCreature::GetDeadSoundName() const
{
	return "default_DeadSound";
}

float AMyCreature::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);
	if(_statCom->IsDead())
	{
		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
	}

	return 0.0f;
}




void AMyCreature::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{

	_isAttcking = false;
	_attackEndedDelegate.Broadcast();
}


void AMyCreature::Init()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCreature::Disable()
{
	SetActorHiddenInGame(true);
	
	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if (controller)
		GetController()->UnPossess();
}



