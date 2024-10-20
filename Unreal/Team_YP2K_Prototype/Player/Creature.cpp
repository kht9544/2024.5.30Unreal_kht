// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Creature.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

#include "Component/StatComponent.h"
#include "Base/MyGameInstance.h"

#include "../Animation/BaseAnimInstance.h"

// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsGuarding = false;
	// cheol
	_StatCom = CreateDefaultSubobject<UStatComponent>(TEXT("StatCom"));
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_StatCom->SetLevelInit(1);

}

void ACreature::Init()
{

}

void ACreature::Disable()
{

}

void ACreature::AttackHit()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 50.0f;

	bool bResult = GetWorld()->SweepMultiByChannel(
		hitResults,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(attackRadius),
		params);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;

	if (bResult)
	{
		drawColor = FColor::Red;

		for (auto &hitResult : hitResults)
		{
			if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
			{
				FDamageEvent DamageEvent;
				//TODO: 데미지 변경
				hitResult.GetActor()->TakeDamage(10.0f, DamageEvent, GetController(), this);
			}
		}
	}
	DrawDebugSphere(GetWorld(), center, attackRadius, 32, drawColor, false, 0.3f);
}

void ACreature::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttacking = false;
	_attackEndedDelegate.Broadcast();
}

float ACreature::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (bIsGuarding)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard"));
	}
	else
	{
		UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayHitReactionMontage();
		}

		FVector KnockbackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockbackDirection.Z = 0.0f;
		KnockbackDirection.Normalize();
		LaunchCharacter(KnockbackDirection * 1000.f, true, true);
		_StatCom->AddCurHp(-Damage);

		if (_StatCom->IsDead())
		{
			SetActorEnableCollision(false);
			auto controller = GetController();
			if (controller)
				GetController()->UnPossess();
			Destroy();
		}
	}

	return 0.0f;
}
