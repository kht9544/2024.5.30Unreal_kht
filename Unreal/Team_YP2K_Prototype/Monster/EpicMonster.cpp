// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/EpicMonster.h"
#include "Base/MyGameInstance.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Monster/AI/AIController_Epic.h"

#include "Engine/DamageEvents.h"

#include "EpicProjectile.h"


#include "../Animation/Monster_N_AnimInstance.h"

AEpicMonster::AEpicMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Griffon
	(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/Griffon/Meshes/SK_Griffon.SK_Griffon'"));

	if (Griffon.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(Griffon.Object);
	}

	//_capsuleComponent->InitCapsuleSize(250.0f, 250.0f); 

	AIControllerClass = AAIController_Epic::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	_launchLength =500.f;
}

void AEpicMonster::BeginPlay()
{
	Super::BeginPlay();

}

void AEpicMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (_StatCom)
	{
		_StatCom->SetEpicLevelInit(1);
	}

	auto _monster_N_AnimInstance = Cast<UMonster_N_AnimInstance>(GetMesh()->GetAnimInstance());
	if (_monster_N_AnimInstance->IsValidLowLevelFast())
	{
		_monster_N_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
		_monster_N_AnimInstance->_attackDelegate.AddUObject(this, &AEpicMonster::testShot);
		_monster_N_AnimInstance->_deathDelegate.AddUObject(this, &AMonster::Disable);
	}
}

void AEpicMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEpicMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEpicMonster::MeleeAttackhit()
{

	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 150.0f;

	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
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


	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		FDamageEvent DamageEvent;
		//hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);

	}

	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);

}

void AEpicMonster::RangedAttackhit()
{
	FName MouthSocketName = TEXT("mouth");


	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 1000.0f;
	float attackRadius = 20.0f;

	FVector forward = GetActorForwardVector();
	FQuat quat = FQuat::FindBetweenVectors(FVector(0, 0, 1), forward); // FRotationMatrix::MakeFromZ(forward).ToQuat();

	FVector start = GetMesh()->GetSocketLocation(MouthSocketName);
	FVector end = start + forward * attackRange;
	FVector center = (start + end) * 0.5f;
	bool bResult = GetWorld()->SweepSingleByChannel
	(
		hitResult,
		start,
		end,
		quat,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeCapsule(attackRadius, attackRange * 0.5f),
		params
	);



	FColor drawColor = FColor::Green;

	// Check if a hit was detected and apply damage if valid
	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;
		FDamageEvent damageEvent;
		FVector hitPoint = hitResult.ImpactPoint;
		_hitPoint = hitResult.ImpactPoint;
		//testShot();

	}


	// DEBUG : DrawCapsule
	DrawDebugCapsule(GetWorld(), center, attackRange * 0.5f, attackRadius, quat, drawColor, false, 2.0f);

}

void AEpicMonster::testShot()
{
	if (_projectileClass)
	{
		FVector forward = GetActorForwardVector();
		FName MouthSocketName = TEXT("wings_1");
		//FVector forward = GetActorForwardVector();
	//	FVector fireLocation = GetActorLocation() + (forward * 150);

		FVector fireLocation = GetMesh()->GetSocketLocation(MouthSocketName);//GetActorLocation() + (forward * 150);

		FRotator fireRotation = forward.Rotation();

		auto projectile = GetWorld()->SpawnActor<AEpicProjectile>(_projectileClass, fireLocation, fireRotation);
		if (projectile)
		{
			projectile->Griffon(this);
			projectile->SetDamage(70); // 데미지 추후 수정 
			projectile->FireInDirection(forward);
			UE_LOG(LogTemp, Error, TEXT("testShot"));
		}
	}
}

