// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Fly.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTTaskNode_Fly : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Fly();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
