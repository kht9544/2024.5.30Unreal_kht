// Fill out your copyright notice in the Description page of Project Settings.

#include "NormalMonster.h"
#include "../Player/MyPlayer.h"
#include "../Animation/Monster_N_AnimInstance.h"
#include "../Player/Creature.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Base/MyGameInstance.h"
#include "../Base/Managers/EffectManager.h"

// Sets default values
ANormalMonster::ANormalMonster()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> PS(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/SK_SKnight_07_full.SK_SKnight_07_full'"));

	if (PS.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(PS.Object);
	}

	_launchLength = 1000.0f;
	_upVector = {0.0f, 0.0f, 200.f};
}

void ANormalMonster::PlayFindEffect()
{
	if (!first)
		return;
	FVector ActorLocation = GetActorLocation();
	ActorLocation.Z += 150.0f;
	EffectManager->Play("NS_FindTarget", ActorLocation);
	SoundManager->PlaySoundOnce("FindTarget_03_Cue", GetActorLocation());
	first = false;
}

// Called when the game starts or when spawned
void ANormalMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ANormalMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	 _monster_N_AnimInstance = Cast<UMonster_N_AnimInstance>(_monster_AnimInstance);
	 if(_monster_N_AnimInstance)
	 {
		_StatCom->SetMonsterLevelInit(1);
	 }
	
}

void ANormalMonster::Attack_AI()
{
	if (_isAttacking == false && _monster_N_AnimInstance != nullptr)
	{
		_monster_N_AnimInstance->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 4;
		_curAttackIndex++;

		_monster_N_AnimInstance->JumpToSection(_curAttackIndex);
	}
}
