// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_NPCAttack.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UBTTask_NPCAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_NPCAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool _isAttacking = false;
};
