// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnim_BossMonster_Instance.h"

UMyAnim_BossMonster_Instance::UMyAnim_BossMonster_Instance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Monster_06
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Anim/Monster/Monster_06_Mongtage.Monster_06_Mongtage'"));

	if (Monster_06.Succeeded())
	{
		_myAnimMontage = Monster_06.Object;
	}
}

void UMyAnim_BossMonster_Instance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

}

void UMyAnim_BossMonster_Instance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}

void UMyAnim_BossMonster_Instance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UMyAnim_BossMonster_Instance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();
}

void UMyAnim_BossMonster_Instance::AnimNotify_Death()
{
	_deathDelegate.Broadcast();
}
