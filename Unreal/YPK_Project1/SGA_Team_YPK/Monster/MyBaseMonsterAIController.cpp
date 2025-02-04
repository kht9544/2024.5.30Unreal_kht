// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseMonsterAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

const FName AMyBaseMonsterAIController::TargetKey(TEXT("Target"));

AMyBaseMonsterAIController::AMyBaseMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/BaseMonsterAI_BB.BaseMonsterAI_BB'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/BaseMonsterAI_BT.BaseMonsterAI_BT'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}

}

void AMyBaseMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* blackBoarComponent = Blackboard;
	if (UseBlackboard(_bb, blackBoarComponent))
	{
		if (RunBehaviorTree(_bt))
		{
			blackBoarComponent->SetValueAsVector(FName(TEXT("FixedPos")), InPawn->GetActorLocation());
			UE_LOG(LogTemp, Log, TEXT("Behavior Tree Succeeded"));
		}
	}

}

void AMyBaseMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void AMyBaseMonsterAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return;

	UNavigationSystemV1* naviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (naviSystem == nullptr)
		return;

	FNavLocation randLocation;

	if (naviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.0f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	}
}

