// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Monster_N_AnimInstance.h"

UMonster_N_AnimInstance::UMonster_N_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Monster_N_01
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/Monster_N_07_AnimMontage.Monster_N_07_AnimMontage'"));

	if (Monster_N_01.Succeeded())
	{
		_myAnimMontage = Monster_N_01.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitReaction
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/NM_HitMotionMontage.NM_HitMotionMontage'"));

	if (HitReaction.Succeeded())
	{
		HitReactionMontage = HitReaction.Object;
	}

}

void UMonster_N_AnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMonster_N_AnimInstance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}


void UMonster_N_AnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UMonster_N_AnimInstance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();
}

void UMonster_N_AnimInstance::AnimNotify_Death()
{
	_deathDelegate.Broadcast();
}
