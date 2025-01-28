// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "Monster_Epic01_Anim.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API UMonster_Epic01_Anim : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	UMonster_Epic01_Anim();

	virtual void PlayAttackFarMontage() override;

	virtual void PlayAttackDotrMontage() override;

	UFUNCTION()
	virtual void AnimNotify_Attackhit() override;

	UFUNCTION()
	virtual void AnimNotify_Death() override;
};
