// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "MyEffectManager.h"
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


	static ConstructorHelpers::FObjectFinder<UDataTable> NPCdata
	(TEXT("/Script/Engine.DataTable'/Game/Data/NPCStatDataTable.NPCStatDataTable'"));
	if (NPCdata.Succeeded())
	{
		_NPCStatTable = NPCdata.Object;
	}

}

void UMyGameInstance::Init()
{
	Super::Init();

	auto statData = GetStatDataByLevel(1);
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

FMyStatData* UMyGameInstance::GetNPCStatDataByLevel(int level)
{
	auto npcStatData = _NPCStatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return npcStatData;
}

void UMyGameInstance::InitializeManagers()
{
	FActorSpawnParameters params;
	params.Name = TEXT("EffectManager");
	_effectManager = GetWorld()->SpawnActor<AMyEffectManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

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
