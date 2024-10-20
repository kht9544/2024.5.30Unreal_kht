// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBTService_Player_FindTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBaseMonsterAIController.h"
#include "MyMonster.h"
#include "MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

UMyBTService_Player_FindTarget::UMyBTService_Player_FindTarget()
{
	NodeName = TEXT("FindMonsterTarget");
	Interval = 0.5f;
}

void UMyBTService_Player_FindTarget::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (currentPawn == nullptr)
		return;

	auto world = GetWorld();
	FVector center = currentPawn->GetActorLocation();
	float searchRadius = 1000.0f;

	if (world == nullptr)
		return;

	TArray<FOverlapResult> overLapResult;
	FCollisionQueryParams qparams(NAME_None, false, currentPawn);

	bool bResult = world->OverlapMultiByChannel(
		overLapResult,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(searchRadius),
		qparams);

	if (bResult)
	{
		for (auto &result : overLapResult)
		{
			auto myCharacter = Cast<AMyMonster>(result.GetActor());
			if (myCharacter != nullptr && !myCharacter->_statCom->IsDead())
			{
				auto myCharacterController = myCharacter->GetController();
				if (myCharacterController != nullptr)
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("MonsterTarget")), myCharacter);
				}
				return;
			}
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("MonsterTarget")), nullptr);
	}
}
