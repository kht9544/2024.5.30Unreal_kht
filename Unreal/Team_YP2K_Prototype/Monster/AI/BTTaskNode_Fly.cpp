// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/BTTaskNode_Fly.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Monster/EpicMonster.h"

#include "GameFramework/CharacterMovementComponent.h" 
#include "Monster/EpicMonster.h"
#include "DrawDebugHelpers.h"  // 디버그용

UBTTaskNode_Fly::UBTTaskNode_Fly()
{
	NodeName = TEXT("Fly");

}

EBTNodeResult::Type UBTTaskNode_Fly::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return EBTNodeResult::Type();
}

