// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "Monster_N_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API UMonster_N_AnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	

public:
	UMonster_N_AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayAttackMontage()override;

	virtual void JumpToSection(int32 sectionIndex) override;

	AttackDelegate _attackDelegate;

	DeathDelegate _deathDelegate;

	//HitMotionDelegate _hitMotionDelegate;


	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();


};
