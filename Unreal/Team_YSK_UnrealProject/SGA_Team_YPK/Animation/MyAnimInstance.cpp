// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MyCreature.h"
#include "GameFramework/PawnMovementComponent.h"


UMyAnimInstance::UMyAnimInstance()
{

	_isFalling = false;
	_isDead = false;
	_weaponDrawn = false;

	_speed = 0;
	_Direction = 0;
	_vertical = 0;
	_horizontal = 0;

}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AMyCreature* myCharacter = Cast<AMyCreature>(TryGetPawnOwner());
	if (myCharacter != nullptr)
	{
		_speed = myCharacter->GetVelocity().Size();
		_isFalling = myCharacter->GetMovementComponent()->IsFalling();
		_Direction = CalculateDirection(myCharacter->GetVelocity(), myCharacter->GetActorRotation());

		_vertical = _speed + (myCharacter->GetVertical() - _speed) * (DeltaSeconds);
		_horizontal = _Direction + (myCharacter->GetHorizontal() - _Direction) * (DeltaSeconds);
		_isDead = (myCharacter->GetCurHp() <= 0);

		_vertical = _vertical + (myCharacter->GetVertical() - _vertical) * (DeltaSeconds);
	}
}

void UMyAnimInstance::JumpToSection(int32 sectionIndex)
{
	FName sectionName = FName(*FString::Printf(TEXT("Attack%d"), sectionIndex));
	Montage_JumpToSection(sectionName);
}

void UMyAnimInstance::PlayAttackMontage()
{
	if (!Montage_IsPlaying(_myAnimMontage))
	{
		Montage_Play(_myAnimMontage);
	}
}

void UMyAnimInstance::PlayRemovAnim()
{
	if (!_weaponDrawn && _RemoveAnimation)
	{
		PlaySlotAnimationAsDynamicMontage(_RemoveAnimation, FName("DefaultSlot"), 0.2f, 0.2f, 1.0f);
		_weaponDrawn = true;

	}
}
