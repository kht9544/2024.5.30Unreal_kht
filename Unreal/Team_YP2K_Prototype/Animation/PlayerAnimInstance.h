// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../Animation/BaseAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */


UCLASS()
class PROTOTYPE_API UPlayerAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	virtual void JumpToSection(int32 sectionIndex) override;
	virtual void PlayAttackMontage() override;


	// 방어 애니메이션 재생 함수 (시작/해제)
	void PlayGuardMontage(bool bIsGuarding);
	void StopGuardMontage();
	// 스킬 애니메이션 재생함수
	void PlaySkill01Montage();
	void PlaySkill02Montage();

	AttackDelegate _attackDelegate;
	DeathDelegate _deathDelegate_Knight;


	UFUNCTION()
	virtual void AnimNotify_Attackhit();

	UFUNCTION()
	virtual void AnimNotify_Death();
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _skill01Montage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skills", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* _skill02Montage;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player", Meta = (AllowPrivateAccess = true))
	class UAnimMontage* _shieldMontage;
	

	FName GuardStartSectionName;
	FName GuardLoopSectionName;
	FName GuardEndSectionName;

};
