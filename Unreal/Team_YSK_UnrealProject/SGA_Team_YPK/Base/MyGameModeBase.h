// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMyGameModeBase();

	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	
	UPROPERTY()
	UClass* _monsterClass;

	UPROPERTY()
	TArray<class AMyBaseMonster*> _basemonsters;

	void MonsterClear();
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_Monster_Instance* _animInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class AMyBaseMonsterAIController* _aiController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 _monsterNum;

	
};

