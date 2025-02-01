// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Boss2Monster.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "AI/AIController_Boss2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/MyPlayer.h"
#include "Base/MyGameInstance.h"
#include "Base/Stage2BossGameModeBase.h"
#include "Engine/DamageEvents.h"
#include "../Animation/Monster_Boss2_AnimInstance.h"
#include "BossFireball.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Base/Managers/EffectManager.h"

ABoss2Monster::ABoss2Monster()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<ABossFireball> BF(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/BossFireball_BP.BossFireball_BP_C'"));
	if (BF.Succeeded())
	{
		_fireball = BF.Class;
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(310.0f);
	GetCapsuleComponent()->SetCapsuleRadius(100.0f);

	AIControllerClass = AAIController_Boss2::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABoss2Monster::BeginPlay()
{
	Super::BeginPlay();
	InitializeFireballPool();
}

void ABoss2Monster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_bossMonster02_AnimInstance = Cast<UMonster_Boss2_AnimInstance>(_monster_AnimInstance);
	if(_bossMonster02_AnimInstance)
	{
		_bossMonster02_AnimInstance->_skillDelegate.AddDynamic(this, &ABoss2Monster::FireballAttack);
	}

	_StatCom->SetBossLevelInit(1);
}

void ABoss2Monster::FireballAttack(FVector Location)
{
	Isfire = true;
	float FireballSpacing = 200.0f;
	FVector InitialLocation = GetActorLocation() + FVector(0, 0, 300.0f);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	int FireballCount = 5;
	float MiddleIndex = (FireballCount - 1) / 2.0f;

	TArray<class ABossFireball *> Fireballs;

	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();

	for (int i = 0; i < FireballCount; i++)
	{
		FVector Offset = RightVector * (i - MiddleIndex) * FireballSpacing;
		FVector SpawnLocation = InitialLocation + Offset;

		ABossFireball *Fireball = FireballPool[i];
		if (Fireball)
		{
			Fireball->SetActorLocation(SpawnLocation);
			Fireball->SetActorHiddenInGame(false);
			Fireball->SetActorEnableCollision(true);
			Fireballs.Add(Fireball);
		}
	}

	if (Fireballs.IsValidIndex(0))
	{
		Fireballs[0]->LaunchTowards(Location);
	}

	for (int i = 1; i < Fireballs.Num(); i++)
	{
		FTimerHandle TimerHandle;

		GetWorldTimerManager().SetTimer(TimerHandle, [this, Fireballs, i, Location]()
										{
            if (Fireballs.IsValidIndex(i) && Fireballs[i])
            {
                FVector TargetLocation = UpdatedLocation();
                Fireballs[i]->LaunchTowards(TargetLocation);
            } }, i * 0.5f, false);
	}

	Isfire = false;
}

FVector ABoss2Monster::UpdatedLocation()
{
	auto AIController = Cast<AAIController_Boss2>(GetController());
	FVector LastVector;

	if (AIController && AIController->GetBlackboardComponent())
	{
		AActor *TargetActor = Cast<AActor>(AIController->GetBlackboardComponent()->GetValueAsObject("Target"));
		if (TargetActor)
		{
			LastVector = TargetActor->GetActorLocation();
			return LastVector;
		}
	}
	return LastVector;
}

float ABoss2Monster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	return 0.0f;
}

void ABoss2Monster::Attack_AI()
{
	if (_isAttacking == false && _bossMonster02_AnimInstance != nullptr)
	{
		_isAttacking = true;
		_bossMonster02_AnimInstance->PlayAttackMontage();
	}
}

void ABoss2Monster::InitializeFireballPool()
{
	if (!_fireball)
		return;

	for (int32 i = 0; i < PoolSize; ++i)
	{
		ABossFireball *Fireball = GetWorld()->SpawnActor<ABossFireball>(_fireball, FVector::ZeroVector, FRotator::ZeroRotator);
		if (Fireball)
		{
			Fireball->SetActorEnableCollision(false);
			Fireball->SetActorHiddenInGame(true);
			FireballPool.Add(Fireball);
		}
	}
}

ABossFireball *ABoss2Monster::GetPooledFireball()
{
	for (ABossFireball *Fireball : FireballPool)
	{
		if (!Fireball->IsActive())
		{
			return Fireball;
		}
		else
		{
			continue;
		}
	}

	ABossFireball *NewFireball = GetWorld()->SpawnActor<ABossFireball>(_fireball, FVector::ZeroVector, FRotator::ZeroRotator);
	if (NewFireball)
	{
		NewFireball->SetActorEnableCollision(false);
		NewFireball->SetActorHiddenInGame(true);
		FireballPool.Add(NewFireball);
	}
	return NewFireball;
}

void ABoss2Monster::Skill_AI(FVector location)
{
	if (_bossMonster02_AnimInstance != nullptr)
	{
		_bossMonster02_AnimInstance->PlaySkillMontage();
		_bossMonster02_AnimInstance->SetTarget(location);
	}
}

void ABoss2Monster::Teleport(FVector location)
{
	float OriginalZ = location.Z;

	FVector TeleportLocation = location + FMath::VRand() * FMath::FRandRange(100.0f, 600.0f);
	TeleportLocation.Z = OriginalZ;

	FVector MinBounds(-1710.0f, -3790.0f, 460.0f);
	FVector MaxBounds(2190.0f, -1270.0f, 460.0f);

	TeleportLocation.X = FMath::Clamp(TeleportLocation.X, MinBounds.X, MaxBounds.X);
	TeleportLocation.Y = FMath::Clamp(TeleportLocation.Y, MinBounds.Y, MaxBounds.Y);
	TeleportLocation.Z = MinBounds.Z;

	SetActorLocation(TeleportLocation, false, nullptr, ETeleportType::TeleportPhysics);

	FRotator CurrentRotation = GetActorRotation();
	FVector DirectionToLocation = location - TeleportLocation;
	FRotator LookAtRotation = DirectionToLocation.Rotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch, LookAtRotation.Yaw, CurrentRotation.Roll);

	SetActorRotation(NewRotation);

	FVector EffectLocation = GetActorLocation();
	EffectLocation.Z -= 300.0f;

	EffectManager->Play(*GetBoss2TeleportEffect(), EffectLocation);
	SoundManager->PlaySound(*GetBoss2TeleportSound(), GetActorLocation());

	Attack_AI();
}

FString ABoss2Monster::GetBoss2AttackEffect() const
{
	return "NS_Mage_LIghtning_Bolt";
}

FString ABoss2Monster::GetBoss2TeleportEffect() const
{
	return "NS_Boss_02_Teleport";
}

FString ABoss2Monster::GetBoss2TeleportSound() const
{
	return "Boss_02_Teleport_Cue";
}
