// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Component/StatComponent.h"
#include "../Item/BaseItem.h"
#include "MyGameInstance.generated.h"

#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

private:

public:
	virtual void Init() override;
	
	class AUIManager* GetUIManager() { return _UIManager; }

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetEpicDataByLevel(int level);
	FMyStatData* GetBossDataByLevel(int level);

	FItemData* GetConsumeItemData(int code);

	UPROPERTY(BlueprintReadWrite, Category = "Stat")
	int32 _playerLevel;

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void SavePlayerStatus(int32 Level);

	UFUNCTION(BlueprintCallable, Category = "Stat")
	void LoadPlayerStatus(int32& Level);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager* _UIManager;

	UPROPERTY()
	UDataTable* _statTable;

	UPROPERTY()
	UDataTable* _EpicstatTable;

	UPROPERTY()
	UDataTable* _BossstatTable;

	UPROPERTY()
	UDataTable* _ConsItemTable;

};
