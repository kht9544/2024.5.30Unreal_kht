// Fill out your copyright notice in the Description page of Project Settings.


#include "UBTService_TakeDamage.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyNPC.h"
#include "UBTService_TakeDamage.h"
#include "MyNPCAIController.h"

UUBTService_TakeDamage::UUBTService_TakeDamage()
{
	NodeName = TEXT("TakeDamageCheck");
	Interval = 0.5f; 
}

void UUBTService_TakeDamage::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AMyNPC* NPCCharacter = Cast<AMyNPC>(OwnerComp.GetAIOwner()->GetPawn());
    if (NPCCharacter)
    {
        float damageReceived = -NPCCharacter->_statCom->AddCurHp(0);

        if (damageReceived < 0)
        {
         
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDamaged"), true);
        }
    }
}

