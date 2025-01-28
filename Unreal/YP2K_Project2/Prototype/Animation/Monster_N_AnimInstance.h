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

	UFUNCTION()
	virtual void AnimNotify_Attackhit() override;

	UFUNCTION()
	virtual void AnimNotify_Death() override;
};
