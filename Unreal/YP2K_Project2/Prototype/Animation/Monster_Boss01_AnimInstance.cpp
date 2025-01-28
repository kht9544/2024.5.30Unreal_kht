// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/Monster_Boss01_AnimInstance.h"

UMonster_Boss01_AnimInstance::UMonster_Boss01_AnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_01(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster01_AnimMontage.BossMonster01_AnimMontage'"));

	if (BM_01.Succeeded())
	{
		_myAnimMontage = BM_01.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_02(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster01_ThrowMontage.BossMonster01_ThrowMontage'"));

	if (BM_02.Succeeded())
	{
		_myUpAttackMontage = BM_02.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_03(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster01_Stun.BossMonster01_Stun'"));
	if (BM_03.Succeeded())
	{
		_myStunMontage = BM_03.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> BM_04(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/BossMonster/BossMonster01_Dashing.BossMonster01_Dashing'"));
	if (BM_04.Succeeded())
	{
		_myDashingMontage = BM_04.Object;
	}
}

void UMonster_Boss01_AnimInstance::PlayUpAttackMontage()
{
	if (!Montage_IsPlaying(_myUpAttackMontage))
	{
		Montage_Play(_myUpAttackMontage);
	}
}

void UMonster_Boss01_AnimInstance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UMonster_Boss01_AnimInstance::AnimNotify_StunEnd()
{
	_stunDelegate.Broadcast();
}

void UMonster_Boss01_AnimInstance::AnimNotify_Attackhit()
{
	Super::AnimNotify_Attackhit();
}

void UMonster_Boss01_AnimInstance::AnimNotify_Death()
{
	Super::AnimNotify_Death();
}
