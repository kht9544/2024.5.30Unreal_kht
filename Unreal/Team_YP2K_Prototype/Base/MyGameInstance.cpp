// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/MyGameInstance.h"

#include "Base/Managers/UIManager.h"

UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> StatData
	(TEXT("/Script/Engine.DataTable'/Game/Data/StatDataTable.StatDataTable'"));

	if (StatData.Succeeded())
	{
		_statTable = StatData.Object;

	}

	// 현재 에픽 스탯데이터테이블 까지완
	static ConstructorHelpers::FObjectFinder<UDataTable> EpicStatData
	(TEXT("/Script/Engine.DataTable'/Game/Data/EpicMonsterDataTable.EpicMonsterDataTable'"));

	if (EpicStatData.Succeeded())
	{
		_EpicstatTable = EpicStatData.Object;

	}

	static ConstructorHelpers::FObjectFinder<UDataTable> BossStatData
	(TEXT("/Script/Engine.DataTable'/Game/Data/BossMonsterDataTable.BossMonsterDataTable'"));

	if (BossStatData.Succeeded())
	{
		_BossstatTable = BossStatData.Object;

	}

	static ConstructorHelpers::FObjectFinder<UDataTable> ConsumItemData
	(TEXT("/Script/Engine.DataTable'/Game/Data/Item/ConsumeItemDataTable.ConsumeItemDataTable'"));

	if (ConsumItemData.Succeeded())
	{
		_ConsItemTable = ConsumItemData.Object;
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	FActorSpawnParameters params;
	params.Name = TEXT("UIManager");
	_UIManager = GetWorld()->SpawnActor<AUIManager>(FVector::ZeroVector, FRotator::ZeroRotator, params);

	LoadPlayerStatus(_playerLevel);
	auto statData = GetStatDataByLevel(_playerLevel);
	auto EpicData = GetEpicDataByLevel(1);
}


FMyStatData* UMyGameInstance::GetStatDataByLevel(int level)
{
	auto statData = _statTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return statData;
}

FMyStatData* UMyGameInstance::GetEpicDataByLevel(int level)
{
	auto EpicStatData = _EpicstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return EpicStatData;
}

FMyStatData* UMyGameInstance::GetBossDataByLevel(int level)
{
	auto BossStatData = _BossstatTable->FindRow<FMyStatData>(*FString::FromInt(level), TEXT(""));
	return BossStatData;
}

FItemData* UMyGameInstance::GetConsumeItemData(int code)
{
	auto ConsumeData = _ConsItemTable->FindRow<FItemData>(*FString::FromInt(code), TEXT(""));
	return ConsumeData;
}

void UMyGameInstance::SavePlayerStatus(int32 Level)
{
	_playerLevel = Level;

}

void UMyGameInstance::LoadPlayerStatus(int32& Level)
{
	Level = _playerLevel;
}
