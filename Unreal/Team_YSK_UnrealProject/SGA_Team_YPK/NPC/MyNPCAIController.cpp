// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"



AMyNPCAIController::AMyNPCAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("/Script/AIModule.BlackboardData'/Game/Blueprint/AI/NPCAI_BB.NPCAI_BB'"));
	if (BB.Succeeded())
	{
		_bb = BB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("/Script/AIModule.BehaviorTree'/Game/Blueprint/AI/NPCAI_BT.NPCAI_BT'"));
	if (BT.Succeeded())
	{
		_bt = BT.Object;
	}
}

void AMyNPCAIController::OnPossess(APawn* InPawn)
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

void AMyNPCAIController::OnUnPossess()
{
	Super::OnUnPossess();

}

void AMyNPCAIController::RandMove()
{
	auto currentPawn = GetPawn();

	if (!currentPawn->IsValidLowLevel())
		return;

	UNavigationSystemV1* NaviSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
	if (NaviSystem == nullptr)
		return;

	FNavLocation randLocation;

	if (NaviSystem->GetRandomPointInNavigableRadius(currentPawn->GetActorLocation(), 500.f, randLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, randLocation);
	}
}
