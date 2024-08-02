// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "MonsterCharacter.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> am(TEXT("/Script/Engine.AnimMontage'/Game/Blueprint/Animation/Monster/MonsterAnimMontage.MonsterAnimMontage'"));

	if (am.Succeeded())
	{
		_monsterMontage = am.Object;
	}
}

void UMonsterAnimInstance::PlayDeadMontage()
{
	if (!Montage_IsPlaying(_monsterMontage))
	{
		Montage_Play(_monsterMontage);
		AMonsterCharacter* monsterCharacter = Cast<AMonsterCharacter>(TryGetPawnOwner());
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AMonsterCharacter* monster = Cast<AMonsterCharacter>(TryGetPawnOwner());
	if (monster != nullptr)
	{
		_isDead = monster->_isDead;
	}
}

void UMonsterAnimInstance::AnimNotify_Dead()
{
	_deadDelegate.Broadcast();
}
