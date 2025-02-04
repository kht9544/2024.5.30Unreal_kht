// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimInstance.h"
#include "MyAnim_Archer_Instance.generated.h"

/**
 * 
 */

UCLASS()
class SGA_TEAM_YPK_API UMyAnim_Archer_Instance : public UMyAnimInstance
{
	GENERATED_BODY()
	

public:
	UMyAnim_Archer_Instance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayAttackMontage()override;

	virtual void JumpToSection(int32 sectionIndex) override;

	AttackDelegate _attackDelegate_Archer;
	DeathDelegate _deathDelegate_Archer;

	UFUNCTION()
	virtual void AnimNotify_Attackstart();

	UFUNCTION()
	virtual void AnimNotify_Death();

};
