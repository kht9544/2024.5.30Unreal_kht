// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerAnimInstance.h"
#include "../Player/Creature.h"
#include "../Player/MyPlayer.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Knignt(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Knight_Montage.Knight_Montage'"));

	if (Knignt.Succeeded())
	{
		_myAnimMontage = Knignt.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Guard(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Shield_Montage.Shield_Montage'"));
	if (Guard.Succeeded())
	{
		_shieldMontage = Guard.Object;
	}

	GuardLoopSectionName = TEXT("GuardLoop");
	GuardEndSectionName = TEXT("GuardEnd");
	GuardStartSectionName = TEXT("GuardStart");

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HitReaction(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/HitMotionMontage.HitMotionMontage'"));
	if (HitReaction.Succeeded())
	{
		HitReactionMontage = HitReaction.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill01Montage(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_01_Mongtage.Skill_01_Mongtage'"));
	if (Skill01Montage.Succeeded())
	{
		_skill01Montage = Skill01Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill02Montage(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_02_Mongtage.Skill_02_Mongtage'"));
	if (Skill02Montage.Succeeded())
	{
		_skill02Montage = Skill02Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill03Montage(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/Skill_03_Montage.Skill_03_Montage'"));
	if (Skill03Montage.Succeeded())
	{
		_skill03Montage = Skill03Montage.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ChangeMontage(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Player/ChangeDragonMontage.ChangeDragonMontage'"));
	if (ChangeMontage.Succeeded())
	{
		_changeMontage = ChangeMontage.Object;
	}
}

void UPlayerAnimInstance::PlayGuardMontage(bool _isGuarding)
{
	if (_isGuarding)
	{
		if (!Montage_IsPlaying(_shieldMontage))
		{
			Montage_Play(_shieldMontage, 1.0f);
			Montage_JumpToSection(FName("GuardStart"), _shieldMontage);
		}
		Montage_JumpToSection(FName("GuardLoop"), _shieldMontage);
	}
	else
	{
		Montage_JumpToSection(FName("GuardEnd"), _shieldMontage);
	}
}

void UPlayerAnimInstance::StopGuardMontage()
{
	if (Montage_IsPlaying(_shieldMontage))
	{
		Montage_Stop(0.0f, _shieldMontage);
	}
}

void UPlayerAnimInstance::PlaySkill01Montage()
{
	if (_skill01Montage)
	{
		Montage_Play(_skill01Montage);
	}
}

void UPlayerAnimInstance::PlaySkill02Montage()
{
	if (_skill02Montage)
	{
		Montage_Play(_skill02Montage);
	}
}

void UPlayerAnimInstance::PlaySkill03Montage()
{
	if (_skill03Montage)
	{
		Montage_Play(_skill03Montage);
	}
}

void UPlayerAnimInstance::PlayChangeMontage()
{
	if (_changeMontage)
	{
		Montage_Play(_changeMontage);
	}
}

void UPlayerAnimInstance::AnimNotify_clickNext()
{
	_comboDelegate.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_Attackhit()
{
	Super::AnimNotify_Attackhit();
}

void UPlayerAnimInstance::AnimNotify_Death()
{
	Super::AnimNotify_Death();
}
