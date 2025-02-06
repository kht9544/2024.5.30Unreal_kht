// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Managers/EffectManager.h"
#include "Managers/SoundManager.h"
#include "Component/StatComponent.h"
#include "Component/InventoryComponent.h"
#include "../Item/BaseItem.h"
#include "Item/Equip/EquipItem.h"
#include "../Component/ShopComponent.h"
#include "MyGameInstance.generated.h"

#define GAMEINSTANCE Cast<UMyGameInstance>(GetWorld()->GetGameInstance())
#define UIManager Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()
#define T_DEFAULT Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->GetUIManager()->GetDefaultTexture()
#define SoundManager Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager()
#define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()

USTRUCT()
struct FPlayerStatsStruct {
    GENERATED_BODY()
    int32 Level, MaxHp, CurHp;
    int32 MaxMp, CurMp;
    int32 Str;
    int32 Dex;
    int32 Int;
    int32 Exp, NextExp, BonusPoint, Money;
    float AttackRadius, AttackRange;
};

UCLASS()
class PROTOTYPE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();
	void SavePlayerStats(class UStatComponent *StatComponent);
	void LoadPlayerStats(class UStatComponent *StatComponent);

	void SaveInventory(class UInventoryComponent *InventoryComponent);
	void LoadInventory(class UInventoryComponent *InventoryComponent);

	void SavePlayerSkeletal(class AMyPlayer *player);
	void LoadPlayerSkeletal(class AMyPlayer *player);

	UPROPERTY()
	TArray<FItemData> SavedInventoryData;

	UPROPERTY()
	TMap<FString, FItemData> SavedEquipData;

	bool GetFirst() { return _firstIn; }
	void SetFirst(bool first) { _firstIn = first; }

	bool GetStage1Clear() { return _stage1Clear; }
	void SetStage1Clear(bool clear) { _stage1Clear = clear; }

	bool GetStage2Clear() { return _stage2Clear; }
	void SetStage2Clear(bool clear) { _stage2Clear = clear; }

	TArray<ABaseItem *> GetInvenItemList();

public:
	virtual void Init() override;

	UFUNCTION()
	void InitializeManagers();

	class AUIManager *GetUIManager() { return _UIManager; }

	FMyStatData *GetStatDataByLevel(int level);
	FMyStatData *GetMonsterDataByLevel(int level);
	FMyStatData *GetEpicDataByLevel(int level);
	FMyStatData *GetBossDataByLevel(int level);
	FMyStatData *GetDragonDataByLevel(int level);

	FItemData *GetConsumeItemData(int code);
	FItemData *GetEquipItemData(int code);

	TArray<FSellings *> GetSellingData(int32 shop);

	ABaseItem *SellDataToItemData(FSellings *data);

	ASoundManager *GetSoundManager() { return _soundManager; }
	AEffectManager *GetEffectManager() { return _effectManager; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio")
	float MasterVolume = 1.0f;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AUIManager *_UIManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ASoundManager *_soundManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AEffectManager *_effectManager;

	UPROPERTY()
	UDataTable *_statTable;

	UPROPERTY()
	UDataTable *_EpicstatTable;

	UPROPERTY()
	UDataTable *_BossstatTable;

	UPROPERTY()
	UDataTable *_MonsterstatTable;

	UPROPERTY()
	UDataTable *_ConsItemTable;
	UPROPERTY()
	UDataTable *_EquipItemTable;

	UPROPERTY()
	UDataTable *_ShopList;

	UPROPERTY()
	TArray<UDataTable *> _ShopLists;

	UPROPERTY()
	UDataTable *_DragonStatTable;

	UPROPERTY()
    FPlayerStatsStruct SavedPlayerStats;

	UPROPERTY()
	TArray<class USkeletalMesh *> SavedSkeletalMeshes;

	UPROPERTY()
	float _savedAttackRadius;

	UPROPERTY()
	float _savedAttackRange;

	UPROPERTY()
	bool _firstIn = true;

	UPROPERTY()
	bool _stage1Clear = false;

	UPROPERTY()
	bool _stage2Clear = false;
};
