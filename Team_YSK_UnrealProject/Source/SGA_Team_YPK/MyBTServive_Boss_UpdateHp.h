// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MyBTServive_Boss_UpdateHp.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyBTServive_Boss_UpdateHp : public UBTService
{
	GENERATED_BODY()
	
public:
	UMyBTServive_Boss_UpdateHp();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
