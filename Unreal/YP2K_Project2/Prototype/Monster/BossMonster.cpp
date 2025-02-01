// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/BossMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_Boss01_AnimInstance.h"
#include "../Player/Creature.h"
#include "../Player/Fireball.h"
#include "../Player/MyDecal.h"
#include "LandDecal.h"
#include "Components/DecalComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Base/MyGameInstance.h"
#include "../Base/Managers/SoundManager.h"
#include "../Base/Managers/UIManager.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "UI/Boss1Widget.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

ABossMonster::ABossMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM(TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster_01.BossMonster_01'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}

	static ConstructorHelpers::FClassFinder<ALandDecal> DA(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/LandDecal_BP.LandDecal_BP_C'"));
	if (DA.Succeeded())
	{
		_landDecal = DA.Class;
	}

	ObstacleDestroyCount = 0;
	DashDistance = 2000.f;
	DashSpeed = 2000.f;
	_dashDecal = nullptr;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_bossMonster01_AnimInstance = Cast<UMonster_Boss01_AnimInstance>(_monster_AnimInstance);
	if(_bossMonster01_AnimInstance)
	{
		_bossMonster01_AnimInstance->_stunDelegate.AddUObject(this, &ABossMonster::StunEnd);
	}

	_StatCom->SetBossLevelInit(1);
}

void ABossMonster::Attack_AI()
{
	Super::Attack_AI();

	FString soundKey;
	if (RandomSectionIndex == 1)
	{
		soundKey = "BossMonsterAttack_Hard";
	}
	else if (RandomSectionIndex == 2)
	{
		soundKey = "BossMonsterPunch";
	}
	else if (RandomSectionIndex == 3)
	{
		soundKey = "BossMonsterPunch";
	}
	SoundManager->PlaySound(soundKey, GetActorLocation());
}

float ABossMonster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void ABossMonster::JumpAttack(FVector TargetLocation)
{
	if (IsJumping || IsStun || IsDashing)
		return;

	JumpStartTime = GetWorld()->GetTimeSeconds();
	IsJumping = true;

	FVector CurrentLocation = GetActorLocation();
	FVector JumpDirection = (TargetLocation - CurrentLocation).GetSafeNormal2D();
	float HorizontalDistance = FVector::Dist2D(TargetLocation, CurrentLocation);

	float JumpHeight = 500.0f;
	float Gravity = GetWorld()->GetGravityZ();
	float JumpVelocityZ = FMath::Sqrt(-2 * Gravity * JumpHeight);

	float TimeToReach = FMath::Sqrt(2 * JumpHeight / -Gravity) +
						FMath::Sqrt(2 * (CurrentLocation.Z - TargetLocation.Z + JumpHeight) / -Gravity);

	FVector JumpVelocity = JumpDirection * (HorizontalDistance / TimeToReach);
	JumpVelocity.Z = JumpVelocityZ;

	FRotator LookAtRotation = (TargetLocation - CurrentLocation).Rotation();
	SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));

	FVector LandingLocation = TargetLocation;
	LandingLocation.Z -= 98.0f;

	LaunchCharacter(JumpVelocity, true, true);

	if (_landDecal)
	{
		ALandDecal *Decal = GetWorld()->SpawnActor<ALandDecal>(_landDecal, LandingLocation, FRotator::ZeroRotator);
	}
}

void ABossMonster::Landed(const FHitResult &Hit)
{
	float LandTime = GetWorld()->GetTimeSeconds();
	JumpDuration = LandTime - JumpStartTime;
	IsJumping = false;

	FVector LandLocation = GetActorLocation();
	TArray<AActor *> OverlappingActors;
	GetOverlappingActors(OverlappingActors, AMyPlayer::StaticClass());

	for (AActor *Actor : OverlappingActors)
	{
		AMyPlayer *Player = Cast<AMyPlayer>(Actor);
		if (Player)
		{
			float Distance = FVector::Dist(LandLocation, Player->GetActorLocation());

			if (Distance <= 600.0f)
			{
				Player->TakeDamage(_StatCom->GetStr(), FDamageEvent(), GetController(), this);
			}
		}
	}
}

void ABossMonster::Dash(FVector TargetLocation)
{
	if (IsDashing || IsStun || IsJumping)
		return;

	if (!_dashDecal)
	{
		_dashDecal = NewObject<UDecalComponent>(this);
		_dashDecal->SetupAttachment(RootComponent);
		_dashDecal->RegisterComponent();
		_dashDecal->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));

		UMaterialInterface *RedDecalMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Script/Engine.Material'/Game/Blueprint/VFX/ReddecalMateral.ReddecalMateral'"));
		if (RedDecalMaterial)
		{
			_dashDecal->SetDecalMaterial(RedDecalMaterial);
		}

		float CharacterWidth = GetCapsuleComponent()->GetScaledCapsuleRadius();
		float DecalScaleX = DashDistance / 250.0f;
		float DecalScaleY = CharacterWidth / 200.0f;
		_dashDecal->SetWorldScale3D(FVector(DecalScaleX, DecalScaleY, 0.01f));
	}

	FVector StartLocation = GetActorLocation();
	DashDirection = (TargetLocation - StartLocation).GetSafeNormal();
	DashDirection.Z = 0.f;

	DashEndLocation = StartLocation + DashDirection * DashDistance;

	FRotator LookAtRotation = DashDirection.Rotation();
	SetActorRotation(FRotator(0.0f, LookAtRotation.Yaw, 0.0f));

	FVector DecalLocation = StartLocation + DashDirection * (DashDistance / 2.0f);
	DecalLocation.Z -= GetActorLocation().Z;
	_dashDecal->SetWorldLocation(DecalLocation);

	FTimerHandle DashDecalTimer;
	GetWorld()->GetTimerManager().SetTimer(DashDecalTimer, this, &ABossMonster::StartDash, 1.0f, false);
}

void ABossMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDashing)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation, DashEndLocation, DeltaTime, DashSpeed);

		FHitResult HitResult;
		SetActorLocation(NewLocation, true, &HitResult);

		if (HitResult.bBlockingHit)
		{
			AMyPlayer *player = Cast<AMyPlayer>(HitResult.GetActor());
			if (player != nullptr)
			{
				DashEnd();
				if (_bossMonster01_AnimInstance)
				{
					_bossMonster01_AnimInstance->PlayUpAttackMontage();
				}

				player->TakeDamage(_StatCom->GetStr(), FDamageEvent(), GetController(), this);
				FVector ThrowDirection = (player->GetActorLocation() - GetActorLocation()).GetSafeNormal();
				ThrowDirection.Z = 1.f;
				FVector ThrowForce = ThrowDirection * 1000.0f;
				player->LaunchCharacter(ThrowForce, true, true);
			}
			else if (HitResult.ImpactPoint.Z >= GetActorLocation().Z)
			{
				if (FVector::DistSquared(NewLocation, DashEndLocation) <= KINDA_SMALL_NUMBER)
				{
					DashEnd();
				}
			}
		}
	}
}

void ABossMonster::StartDash()
{
	IsDashing = true;

	if (IsDashing == true)
	{
		_bossMonster01_AnimInstance->PlayDashMontage();
	}

	if (_dashDecal)
	{
		_dashDecal->DestroyComponent();
		_dashDecal = nullptr;
	}

	FTimerHandle DashTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DashTimerHandle, this, &ABossMonster::DashEnd, DashDistance / DashSpeed, false);
}

void ABossMonster::DashEnd()
{
	IsDashing = false;
	GetCharacterMovement()->StopMovementImmediately();
}

void ABossMonster::StunEnd()
{
	IsStun = false;
}

void ABossMonster::DestroyObstacle()
{
	IsStun = true;
	ObstacleDestroyCount++;
	if (UIManager->GetBossUI())
	{
		UIManager->GetBossUI()->UpdateObstacleIcons(ObstacleDestroyCount);
		UIManager->GetBossUI()->UpdateHPBarColor(ObstacleDestroyCount);
	}
	_bossMonster01_AnimInstance->PlayStunMontage();
	GetCharacterMovement()->StopMovementImmediately();
}
