// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimInstance.h"
#include "MyAnim_Knight_Instance.generated.h"

/**
 * 
 */

UCLASS()
class SGA_TEAM_YPK_API UMyAnim_Knight_Instance : public UMyAnimInstance
{
	GENERATED_BODY()
	

public:
	UMyAnim_Knight_Instance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	virtual void PlayAttackMontage() override;

	virtual void JumpToSection(int32 sectionIndex) override;

	AttackDelegate _attackDelegate;
	DeathDelegate _deathDelegate_Knight;


	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();

};
