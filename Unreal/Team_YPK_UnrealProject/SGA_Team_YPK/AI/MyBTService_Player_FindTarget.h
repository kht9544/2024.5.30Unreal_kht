// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTService_Player_FindTarget.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyBTService_Player_FindTarget : public UBTService
{
	GENERATED_BODY()
public:
	UMyBTService_Player_FindTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
