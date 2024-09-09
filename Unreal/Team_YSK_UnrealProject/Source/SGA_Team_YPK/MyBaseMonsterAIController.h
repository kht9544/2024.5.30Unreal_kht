// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyBaseMonsterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyBaseMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMyBaseMonsterAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	static const FName TargetKey;

	void RandMove();

private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
};
