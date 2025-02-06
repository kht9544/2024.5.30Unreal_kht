// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/BaseAnimInstance.h"
#include "DragonAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API UDragonAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	UDragonAnimInstance();

	UFUNCTION()
	virtual void AnimNotify_Attackhit() override;

	UFUNCTION()
	virtual void AnimNotify_Death() override;

	void SetJumping(bool bJumping) { bIsJumping = bJumping; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Animation")
	bool bIsJumping;
};
