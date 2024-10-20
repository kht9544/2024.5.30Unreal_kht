// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnim_Archer_Instance.h"

UMyAnim_Archer_Instance::UMyAnim_Archer_Instance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Archer
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Anim/Player/Archer_Montage.Archer_Montage'"));

	if (Archer.Succeeded())
	{
		_myAnimMontage = Archer.Object;
	}
}

void UMyAnim_Archer_Instance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UMyAnim_Archer_Instance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}

void UMyAnim_Archer_Instance::JumpToSection(int32 sectionIndex)
{
	Super::JumpToSection(sectionIndex);
}

void UMyAnim_Archer_Instance::AnimNotify_Attackstart()
{
	_attackDelegate_Archer.Broadcast();
}

void UMyAnim_Archer_Instance::AnimNotify_Death()
{
	_deathDelegate_Archer.Broadcast();
}
