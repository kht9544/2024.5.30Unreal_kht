// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "MyBTTaskNode_BossSkiil.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyBTTaskNode_BossSkiil : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UMyBTTaskNode_BossSkiil();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool _isAttacking = false;
};
