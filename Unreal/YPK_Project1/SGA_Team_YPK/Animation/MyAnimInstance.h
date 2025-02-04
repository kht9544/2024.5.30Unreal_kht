// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
DECLARE_MULTICAST_DELEGATE(AttackDelegate);
DECLARE_MULTICAST_DELEGATE(DeathDelegate);

DECLARE_MULTICAST_DELEGATE(RemoveDelegate);

UCLASS()
class SGA_TEAM_YPK_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	

public:
	UMyAnimInstance();
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void JumpToSection(int32 sectionIndex);
	virtual void PlayAttackMontage();
	virtual void PlayRemovAnim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _isDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _vertical;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float _horizontal;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _myAnimMontage;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool _weaponDrawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", Meta = (AllowPrivateAccess = true))
	class UAnimSequence* _RemoveAnimation;
};
