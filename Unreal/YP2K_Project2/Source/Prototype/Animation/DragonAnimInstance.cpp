// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/DragonAnimInstance.h"
#include "GameFramework/Character.h"

UDragonAnimInstance::UDragonAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Dragon
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Dragon_GroundAttkack_AnimMontage.Dragon_GroundAttkack_AnimMontage'"));

	if (Dragon.Succeeded())
	{
		_myAnimMontage = Dragon.Object;
	}

}

void UDragonAnimInstance::AnimNotify_Attackhit()
{
	Super::AnimNotify_Attackhit();
}

void UDragonAnimInstance::AnimNotify_Death()
{
	Super::AnimNotify_Death();
}
