// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyBossAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyBossAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;


private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
	
};
