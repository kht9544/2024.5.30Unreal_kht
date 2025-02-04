// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandPos.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_FindRandPos::UBTTask_FindRandPos()
{
	NodeName = TEXT("FindRandPos");
}

EBTNodeResult::Type UBTTask_FindRandPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return EBTNodeResult::Type::Failed;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return EBTNodeResult::Type::Failed;

	FNavLocation randLocation;

	FVector fixedPos = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName(TEXT("FixedPos")));

	if (naviSystem->GetRandomPointInNavigableRadius(fixedPos, 500.0f, randLocation))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(FName(TEXT("RandPos")), randLocation);
		return EBTNodeResult::Type::Succeeded;
	}

	return result;
}
