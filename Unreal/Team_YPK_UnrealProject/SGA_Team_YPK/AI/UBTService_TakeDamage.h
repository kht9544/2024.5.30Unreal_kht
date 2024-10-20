// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UBTService_TakeDamage.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UUBTService_TakeDamage : public UBTService
{
	GENERATED_BODY()

public:
	UUBTService_TakeDamage();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
