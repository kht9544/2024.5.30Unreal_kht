// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
//TODO : YSR Particle
#include "MyEffectManager.h"
//TODO : YSR Sound
#include "MySoundManager.h"

#include "MyBossMonster.h"
#include "MyBossAIController.h"



UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable
	(TEXT("/Script/Engine.DataTable'/Game/Data/MyStatDataTable.MyStatDataTable'"));

	if (dataTable.Succeeded())
	{
		_statTable = dataTable.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable> DT
	(TEXT("/Script/Engine.DataTable'/Game/Data/BossStatDataTable.BossStatDataTable'"));
	if (DT.Succeeded())
	{
		_bossStatTable = DT.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();
	LoadPlayerStatus(_playerLevel); 

	auto statData = GetStatDataByLevel(_playerLevel);
	auto bossData = GetBossStatDataByLevel(1);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UMyGameInstance::InitializeManagers, 0.1f, false);
}


FMyStatData* UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}

FMyStatData* UMyGameInstance::GetBossStatDataByLevel(int level)
{
	auto bossStatData = _bossStatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return bossStatData;
}

void UMyGameInstance::InitializeManagers()
{
	//TODO : YSR Particle
	FActorSpawnParameters params;
	params.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<AMyEffectManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	//TODO : YSR Sound
	params.Name = TEXT("SoundManager");
	_soundManager = GetWorld()->SpawnActor<AMySoundManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);
}

void UMyGameInstance::SavePlayerStatus(int32 Level)
{
	_playerLevel = Level;
}

void UMyGameInstance::LoadPlayerStatus(int32& Level)
{
	Level = _playerLevel;
}
