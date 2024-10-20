// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BossMonster.h"


ABossMonster::ABossMonster()
{
    PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SM( TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/SK_SKnight_07_full.SK_SKnight_07_full'"));

	if (SM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SM.Object);
	}
}

void ABossMonster::BeginPlay()
{
    Super::BeginPlay();
}

void ABossMonster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
	if (_StatCom)
	{
		_StatCom->SetBossLevelInit(1);
	}
}

bool ABossMonster::PerformGimmick()
{
    UE_LOG(LogTemp, Warning, TEXT("StartGimmick"));

    

    return false;
}
