// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(AttackDelegate);

/**
 * 
 */
UCLASS()
class TPS_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();

	void PlayAttackMontage();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void JumpToSection(int32 sectionIndex);
	UFUNCTION()
	void AnimNotify_AttackHit();

	AttackDelegate _attackDelegate;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Pawn,Meta = (AllowPrivateAccess = true))
	float _speed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Pawn,Meta=(AllowPrivateAccess = true))
	bool _IsFalling;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true));
	class UAnimMontage* _myAnimMontage;
	
};
