// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBossMonster.h"
#include "MyAggroComponent.h"
#include "MyAnim_BossMonster_Instance.h"
#include "MyPlayer.h"
#include "MyDecalActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "MyBaseMonsterAIController.h"

AMyBossMonster::AMyBossMonster()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_06/mesh/SK_SKnight_full_06.SK_SKnight_full_06'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	AIControllerClass = AMyBaseMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	_aggroCom = CreateDefaultSubobject<UMyAggroComponent>(TEXT("AggroComponent"));

	_exp = 20;
}

void AMyBossMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance = Cast<UMyAnim_BossMonster_Instance>(GetMesh()->GetAnimInstance());
	if (_animInstance->IsValidLowLevelFast())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCreature::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCreature::Attackhit);
		_animInstance->_deathDelegate.AddUObject(this, &AMyMonster::Disable);
	}
}

float AMyBossMonster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (_aggroCom)
	{
		AMyPlayer *player = Cast<AMyPlayer>(DamageCauser);
		if (player)
		{
			_aggroCom->RegisterDamage(player, Damage);
		}
	}
	return 0.0f;
}

void AMyBossMonster::Attack_AI()
{
	if (_statCom->IsDead())
		return;

	if (_isAttcking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);

		if (_curAttackIndex == 2)
		{
			AMyPlayer *target = _aggroCom->GetTopAggroTarget();
			if (target != nullptr)
			{
				FVector tlocation = target->GetActorLocation();
				TargetAreaAttack(tlocation);
			}
		}
	}
}

void AMyBossMonster::RandAreaAttack()
{
	FVector BossLocation = GetActorLocation();
	FVector RandomLocation = UKismetMathLibrary::RandomPointInBoundingBox(BossLocation, FVector(1000.f, 1000.f, 0.f));
	RandomLocation.Z = 0.f;
	TargetAreaAttack(RandomLocation);
}

void AMyBossMonster::TargetAreaAttack(FVector target)
{
	if (_decal)
	{
		UWorld *World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			target.Z = 0.0f;
			AMyDecalActor *Decal = World->SpawnActor<AMyDecalActor>(_decal, target, FRotator::ZeroRotator, SpawnParams);
		}
	}
}

void AMyBossMonster::DropReword()
{
	Super::DropReword();
}
