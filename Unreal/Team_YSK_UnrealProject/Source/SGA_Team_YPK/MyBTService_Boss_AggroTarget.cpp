// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTService_Boss_AggroTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBossAIController.h"
#include "MyBossMonster.h"
#include "MyPlayer.h"
#include "MyAggroComponent.h"

UMyBTService_Boss_AggroTarget::UMyBTService_Boss_AggroTarget()
{
    NodeName = TEXT("FindAggroTarget");
    Interval = 0.5f;
}

void UMyBTService_Boss_AggroTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (currentPawn == nullptr)
        return;

    AMyBossMonster* boss = Cast<AMyBossMonster>(currentPawn);
    UMyAggroComponent* aggro = boss->_aggroCom;
    if (aggro != nullptr)
    {
        AMyPlayer* target = aggro->GetTopAggroTarget();
        if (target && !target->_statCom->IsDead())
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", target);
        }
        else
        {
            OwnerComp.GetBlackboardComponent()->ClearValue("Target");
        }
    }
}
