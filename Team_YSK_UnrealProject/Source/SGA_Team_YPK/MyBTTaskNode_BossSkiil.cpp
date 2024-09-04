// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTaskNode_BossSkiil.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBaseMonsterAIController.h"
#include "MyBossMonster.h"
#include "TimerManager.h" 
#include "MyPlayer.h"

UMyBTTaskNode_BossSkiil::UMyBTTaskNode_BossSkiil()
{
    NodeName = TEXT("Skill");
}


EBTNodeResult::Type UMyBTTaskNode_BossSkiil::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto boss = Cast<AMyBossMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (boss == nullptr)
		return EBTNodeResult::Failed;

	boss->RandAreaAttack();
	_isAttacking = true;

	return result;
}

void UMyBTTaskNode_BossSkiil::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    if (_isAttacking)
    {
        _isAttacking = false;
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }
		
}
