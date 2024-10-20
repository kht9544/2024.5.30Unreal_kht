// Fill out your copyright notice in the Description page of Project Settings.



#include "BTService_TakeDamageFindTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyBaseMonsterAIController.h"
#include "BTService_TakeDamageFindTarget.h"

#include "MyPlayer.h"
#include "DrawDebugHelpers.h"
#include "Engine/OverlapResult.h"

#include "MyNPC.h"
#include "MyNPCAIController.h"

UBTService_TakeDamageFindTarget::UBTService_TakeDamageFindTarget()
{
	NodeName = TEXT("TakeDamageFindTarget");

}

void UBTService_TakeDamageFindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto currentPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (currentPawn == nullptr)
		return;

	auto world = GetWorld();
	FVector center = currentPawn->GetActorLocation();
	float searchRadius = 500.0f;

	if (world == nullptr)
		return;

	TArray<FOverlapResult> overLapResult;
	FCollisionQueryParams qparams(NAME_None, false, currentPawn);

	bool bResult = world->OverlapMultiByChannel
	(
		overLapResult,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(searchRadius),
		qparams
	);

	AMyNPC* NPCCharacter = Cast<AMyNPC>(OwnerComp.GetAIOwner()->GetPawn());
	if (NPCCharacter)
	{
		float damageReceived = -NPCCharacter->_statCom->AddCurHp(0);

		if (damageReceived < 0)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsBool(FName("IsDamaged"), true);

			if (bResult)
			{
				for (auto& result : overLapResult)
				{
					auto myCharacter = Cast<AMyPlayer>(result.GetActor());

					if (myCharacter != nullptr)
					{
						auto myCharacterController = myCharacter->GetController();
						if (myCharacterController != nullptr && myCharacterController->IsPlayerController())
						{
							OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), myCharacter);
						}

						return;
					}
				}
			}


		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(FName(TEXT("Target")), nullptr);
		}
	}
}
