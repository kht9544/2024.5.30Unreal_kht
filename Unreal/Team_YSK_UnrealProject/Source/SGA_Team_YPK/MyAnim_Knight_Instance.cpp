// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnim_Knight_Instance.h"

UMyAnim_Knight_Instance::UMyAnim_Knight_Instance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Knignt
	(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Anim/Player/Knight_Montage.Knight_Montage'"));

	if (Knignt.Succeeded())
	{
		_myAnimMontage = Knignt.Object;
	}

}

void UMyAnim_Knight_Instance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);


}

void UMyAnim_Knight_Instance::PlayAttackMontage()
{
	Super::PlayAttackMontage();
}

void UMyAnim_Knight_Instance::JumpToSection(int32 sectionIndex)
{
 	Super::JumpToSection(sectionIndex);
}

void UMyAnim_Knight_Instance::AnimNotify_Attackhit()
{
	_attackDelegate.Broadcast();

}

void UMyAnim_Knight_Instance::AnimNotify_Death()
{
	_deathDelegate_Knight.Broadcast();
}
