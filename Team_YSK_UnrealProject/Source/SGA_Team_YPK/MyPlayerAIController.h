// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyPlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyPlayerAIController : public AAIController
{
	GENERATED_BODY()
public:
	AMyPlayerAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	void RandMove();

private:
	UPROPERTY()
	class UBlackboardData* _bb;

	UPROPERTY()
	class UBehaviorTree* _bt;
	
};
