// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_Boss_AggroTarget.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyBTService_Boss_AggroTarget : public UBTService
{
	GENERATED_BODY()

	UMyBTService_Boss_AggroTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
