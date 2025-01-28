// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(AttackDelegate);
DECLARE_MULTICAST_DELEGATE(DeathDelegate);
DECLARE_MULTICAST_DELEGATE(ComboDelegate);

UCLASS()
class PROTOTYPE_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBaseAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void JumpToSection(int32 sectionIndex);
	virtual void PlayAttackMontage();
	virtual void PlayStunMontage();
	virtual void PlayDashMontage();
	virtual void PlayAttackFarMontage();
	virtual void PlayAttackDotrMontage();

	void PlayHitReactionMontage();

	AttackDelegate _attackDelegate;
	DeathDelegate _deathDelegate;

	virtual void AnimNotify_Attackhit();

	virtual void AnimNotify_Death();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = true))
	float _speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", Meta = (AllowPrivateAccess = true))
	bool _isFalling;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", Meta = (AllowPrivateAccess = true))
	float _Direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", Meta = (AllowPrivateAccess = true))
	float _vertical;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", Meta = (AllowPrivateAccess = true))
	float _horizontal;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", Meta = (AllowPrivateAccess = true))
	bool _isDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess = true))
	class UAnimMontage *_myAnimMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage *HitReactionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stun", Meta = (AllowPrivateAccess = true))
	class UAnimMontage *_myStunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stun", Meta = (AllowPrivateAccess = true))
	class UAnimMontage *_myDashingMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = true))
	class UAnimMontage *_attackFarMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = true))
	class UAnimMontage *_attackMagicMontage;
};
