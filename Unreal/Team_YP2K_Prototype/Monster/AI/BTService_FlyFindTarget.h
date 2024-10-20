// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FlyFindTarget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UBTService_FlyFindTarget : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_FlyFindTarget();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;



};