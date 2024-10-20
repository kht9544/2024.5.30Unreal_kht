// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_Player_CanAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBaseMonsterAIController.h"
#include "MyMonster.h"
#include "MyPlayer.h"


UBTDecorator_Player_CanAttack::UBTDecorator_Player_CanAttack()
{
    NodeName = TEXT("PlayerCanAttack");
}

bool UBTDecorator_Player_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
    bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto target = Cast<AMyMonster>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName(TEXT("MonsterTarget"))));

	if (currentPawn == nullptr || target == nullptr)
		return false;

	float distance = target->GetDistanceTo(currentPawn);

	return distance < 600.0f;

	return result;
}
