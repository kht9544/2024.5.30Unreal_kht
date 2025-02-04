// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Player_Attack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBaseMonsterAIController.h"
#include "MyMonster.h"
#include "MyPlayer.h"


UBTTaskNode_Player_Attack::UBTTaskNode_Player_Attack()
{
    NodeName = TEXT("PlayerAttack");
}

EBTNodeResult::Type UBTTaskNode_Player_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<AMyPlayer>(OwnerComp.GetAIOwner()->GetPawn());
	if (character == nullptr)
		return EBTNodeResult::Failed;

	character->Attack_AI();
	_isAttacking = true;

	character->_attackEndedDelegate.AddLambda(
		[this]() -> void
		{
			this->_isAttacking = false;
		});

	return result;
}

void UBTTaskNode_Player_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

}
