// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBaseMonster.h"
#include "MyStatComponent.h"
#include "MyItem.h"
#include "MyInvenComponent.h"
#include "MyAnim_Monster_Instance.h"
#include "MyBaseMonsterAIController.h"
#include "MyGameInstance.h"
#include "MySoundManager.h"

AMyBaseMonster::AMyBaseMonster()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm
	(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_01/mesh/SK_SKnigh_01_full.SK_SKnigh_01_full'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_exp = 10;
	_Dropmoney = 3;
}

void AMyBaseMonster::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; ++i)
	{
		AMyNPCItem* newItem = GetWorld()->SpawnActor<AMyNPCItem>();
		newItem->Disable();
		if (newItem)
		{
			_invenCom->AddItem(newItem);
		}
	}
	
}

void AMyBaseMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_aiController = Cast<AMyBaseMonsterAIController>(GetController());

	_animInstance = Cast<UMyAnim_Monster_Instance>(GetMesh()->GetAnimInstance());
	if (_animInstance->IsValidLowLevelFast())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCreature::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCreature::Attackhit);
		_animInstance->_deathDelegate.AddUObject(this, &AMyMonster::Disable);
	}

}

FString AMyBaseMonster::GetHitParticleName() const
{
	return "ky_flash1";
}

FString AMyBaseMonster::GetHitSoundName() const
{
	return "MyMonster_Atk_Hit";
}

FString AMyBaseMonster::GetDeadSoundName() const
{
	return "MyMonstere_Dead";
}



void AMyBaseMonster::Attack_AI()
{
	if (_statCom->IsDead())
	{
		FVector missLocation = GetActorLocation();
		SoundManager->PlaySound("MyMonstere_Dead", missLocation);
		return;
	}

	if (_isAttcking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
	}

}


