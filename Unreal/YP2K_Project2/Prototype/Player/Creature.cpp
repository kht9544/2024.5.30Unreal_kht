// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/Creature.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

#include "Component/StatComponent.h"
#include "Base/MyGameInstance.h"

#include "../Animation/BaseAnimInstance.h"
#include "../Base/Managers/SoundManager.h"
#include "../Player/MyPlayer.h"

// Sets default values
ACreature::ACreature()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_isGuarding = false;
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
}

void ACreature::Disable()
{
	SoundManager->PlaySound(*GetSoundName(ESoundType::DeadSound), this->GetActorLocation());
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if (controller)
		GetController()->UnPossess();
}

void ACreature::AttackHit()
{
	TArray<FHitResult> hitResults;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = _StatCom->GetAttackRange();
	float attackRadius = _StatCom->GetAttackRadius();

	FVector capsuleCenter = GetActorLocation() + GetActorForwardVector() * (attackRange * 0.5f);

	FQuat capsuleRotation = FQuat::FindBetweenNormals(FVector::UpVector, GetActorForwardVector());

	bool bResult = GetWorld()->SweepMultiByChannel(
		hitResults,
		capsuleCenter,
		capsuleCenter,
		capsuleRotation,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params);

	if (bResult)
	{
		for (auto &hitResult : hitResults)
		{
			if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
			{
				FDamageEvent DamageEvent;
				hitResult.GetActor()->TakeDamage(_StatCom->GetStr(), DamageEvent, GetController(), this);

				_hitPoint = hitResult.ImpactPoint;
				SoundManager->PlaySound(*GetSoundName(ESoundType::HitSound), _hitPoint);
				EffectManager->Play(*GetSoundName(ESoundType::PlayerAttackHitEffect), _hitPoint);
				break;
			}
		}
	}
	else
	{
		FVector missLocation = GetActorLocation();

		SoundManager->PlaySound(*GetSoundName(ESoundType::SwingSound), missLocation);
	}
}

FString ACreature::GetSoundName(ESoundType SoundType) const
{
    switch (SoundType)
    {
    case ESoundType::HitSound: return "default_hit_sound";
    case ESoundType::SwingSound: return "default_SwingAttackSound";
    case ESoundType::GuardOn: return "default_ShieldSound";
    case ESoundType::GuardOff: return "default_ShieldSound";
    case ESoundType::DeadSound: return "default_DeadSound";
    case ESoundType::SkillSound01: return "default_Skill01";
    case ESoundType::SkillSound02: return "default_Skill02";
    case ESoundType::SkillSound03: return "default_Skill03";
    case ESoundType::SkillSound03Shout: return "default_Skill03_Shout";
    case ESoundType::SkillSound04Start: return "default_Skill04_Start";
    case ESoundType::SkillSound04Durring: return "default_Skill04_Durring";
    case ESoundType::BossMonsterAttack: return "default_BossMonsterAttack";
    case ESoundType::SkillParticleEffect02: return "default_Skill02_Effect";
    case ESoundType::PlayerAttackHitEffect: return "default_AttackHit_Effect";
    case ESoundType::EpicAttackFarSound: return "default_Sound";
    case ESoundType::EpicAttackMagicDotSound: return "default_Sound";
    case ESoundType::PlayerSkillEffect04Start: return "default_Start";
    case ESoundType::PlayerSkillEffect04Durring: return "default_Durring";
    case ESoundType::UIBaseSound: return "default_Sound";
    case ESoundType::EpicSkeletonEffect: return "default_Effect";
    case ESoundType::EpicSpawnSound: return "default_Spawn";
    case ESoundType::LevelUpSound: return "default_LevelUpSound";
    default: return "Unknown_Sound";
    }
}



void ACreature::OnAttackEnded(UAnimMontage *Montage, bool bInterrupted)
{
	_isAttacking = false;
	_attackEndedDelegate.Broadcast();
}

float ACreature::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	FVector AttackDirection = DamageCauser->GetActorLocation() - GetActorLocation();
	AttackDirection.Z = 0.0f;
	AttackDirection.Normalize();

	FVector GuardDirection = GetActorForwardVector();

	float DotProduct = FVector::DotProduct(GuardDirection, AttackDirection);
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);

	const float GuardAngle = 90.0f;

	if (_isGuarding && Angle <= GuardAngle)
	{
		SoundManager->PlaySound(*GetSoundName(ESoundType::GuardOn), _hitPoint);
	}
	else
	{
		UBaseAnimInstance *AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayHitReactionMontage();
		}

		SoundManager->PlaySound(*GetSoundName(ESoundType::GuardOff), _hitPoint);

		FVector KnockbackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockbackDirection.Z = 0.0f;
		KnockbackDirection.Normalize();
		LaunchCharacter(KnockbackDirection * 1000.f, true, true);
		_StatCom->AddCurHp(-Damage);
	}

	return 0.0f;
}
