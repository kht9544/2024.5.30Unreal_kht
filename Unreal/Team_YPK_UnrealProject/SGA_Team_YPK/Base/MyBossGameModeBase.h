// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyBossGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyBossGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyBossGameModeBase();

	virtual void BeginPlay() override; 

	void PlayLevelSequence();

	UFUNCTION()
	void OnSequenceFinished();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMyBossMonster> _bossMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UMyAggroUserWidget> _aggroUI;
};
