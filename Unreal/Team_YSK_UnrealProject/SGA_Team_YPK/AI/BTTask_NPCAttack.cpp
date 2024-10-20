// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NPCAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyPlayer.h"
#include "MyNPC.h"
#include "MyNPCAIController.h"
#include "BTTask_NPCAttack.h"

UBTTask_NPCAttack::UBTTask_NPCAttack()
{
	NodeName = TEXT("NPC Attack");

}

EBTNodeResult::Type UBTTask_NPCAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto character = Cast<AMyNPC>(OwnerComp.GetAIOwner()->GetPawn());
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

void UBTTask_NPCAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (_isAttacking == false)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
