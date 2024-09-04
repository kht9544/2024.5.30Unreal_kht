// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBossAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AMyBossAIController::AMyBossAIController()
{
     static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BossAI_BB.BossAI_BB'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BossAI_BT.BossAI_BT'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}


void AMyBossAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

	UBlackboardComponent* blackBoarComponent = Blackboard;
	if (UseBlackboard(_bb, blackBoarComponent))
	{
		if (RunBehaviorTree(_bt))
		{
			blackBoarComponent->SetValueAsVector(FName(TEXT("FixedPos")), InPawn->GetActorLocation());
		}
	}
    
   
}

void AMyBossAIController::OnUnPossess()
{
    Super::OnUnPossess();
}

