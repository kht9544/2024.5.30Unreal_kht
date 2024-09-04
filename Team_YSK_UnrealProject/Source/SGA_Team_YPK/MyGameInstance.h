// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyStatComponent.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

 //TODO : YSR Particle
class AMyEffectManager;
class AMySoundManager;
#define EffectManager Cast<UMyGameInstance>(GetGameInstance())->GetEffectManager()
#define SoundManager Cast<UMyGameInstance>(GetGameInstance())->GetSoundManager()

UCLASS()
class SGA_TEAM_YPK_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;

	FMyStatData* GetStatDataByLevel(int level);
	FMyStatData* GetBossStatDataByLevel(int level);

	AMyEffectManager* GetEffectManager() { return _effectManager; }
	AMySoundManager* GetSoundManager() { return _soundManager; }
	UFUNCTION()
	void InitializeManagers();

	UPROPERTY(BlueprintReadWrite, Category = "Stat")
    int32 _playerLevel;

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void SavePlayerStatus(int32 Level);

    UFUNCTION(BlueprintCallable, Category = "Stat")
    void LoadPlayerStatus(int32& Level);
	

private:
	UPROPERTY()
	class UDataTable* _statTable;

	UPROPERTY()
	class UDataTable* _bossStatTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMyEffectManager* _effectManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AMySoundManager* _soundManager;


};
