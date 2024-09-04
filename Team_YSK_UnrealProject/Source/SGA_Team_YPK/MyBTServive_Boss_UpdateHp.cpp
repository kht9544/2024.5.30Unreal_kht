// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTServive_Boss_UpdateHp.h"
#include "MyBossMonster.h"
#include "MyStatComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBossAIController.h"


UMyBTServive_Boss_UpdateHp::UMyBTServive_Boss_UpdateHp()
{
     NodeName = TEXT("UpdateHpPersent");
}

void UMyBTServive_Boss_UpdateHp::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (currentPawn == nullptr)
        return;

    AMyBossMonster* boss = Cast<AMyBossMonster>(currentPawn);
    UMyStatComponent* stat = boss->_statCom;
    if (stat != nullptr)
    {
        float HealthPercentage = stat->HpRatio();
        OwnerComp.GetBlackboardComponent()->SetValueAsFloat("HpPersent", HealthPercentage);
    }
}
