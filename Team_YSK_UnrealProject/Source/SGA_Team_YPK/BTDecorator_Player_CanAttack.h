// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Player_CanAttack.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UBTDecorator_Player_CanAttack : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_Player_CanAttack();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	
};
