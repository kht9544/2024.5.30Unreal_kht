// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "MyBaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyPlayerController.h"
#include "MyBaseMonsterAIController.h"
#include "MyAnim_Monster_Instance.h"
#include "MyGameInstance.h"
#include "MyPlayer.h"
#include "MyStatComponent.h"
#include "Kismet/GameplayStatics.h"

AMyGameModeBase::AMyGameModeBase() : _monsterNum(5)
{
	static ConstructorHelpers::FClassFinder<AMyBaseMonster>
		myMonster(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/MyBaseMonster_BP.MyBaseMonster_BP_C'"));
	if (myMonster.Succeeded())
	{
		_monsterClass = myMonster.Class;
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyPlayer *PlayerCharacter = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (PlayerCharacter)
	{
		PlayerCharacter->ShowHP();
		UMyStatComponent *StatComponent = PlayerCharacter->FindComponentByClass<UMyStatComponent>();
		if (StatComponent)
		{
			PlayerCharacter->_statCom->SetLevelAndInit(1);
		}
	}

	FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(100, 0.0f, 100.0f);
	FRotator rotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

	for (int i = 0; i < _monsterNum; i++)
	{
		location.X += 700.0 * i;
		location.Y += 700.0f;
		location.Z = 100.0f;

		AMyBaseMonster *SpawnedActor = GetWorld()->SpawnActor<AMyBaseMonster>(_monsterClass, FVector(0.0f, 0.0f, 100.0f), FRotator::ZeroRotator);
		if (SpawnedActor)
		{
			SpawnedActor->SetActorLocation(location);
			SpawnedActor->SpawnDefaultController();
			_basemonsters.Add(SpawnedActor);
		}
	}

	for (auto monster : _basemonsters)
	{
		_animInstance = Cast<UMyAnim_Monster_Instance>(monster->GetMesh()->GetAnimInstance());
		if (_animInstance->IsValidLowLevelFast())
		{
			_animInstance->_deathDelegate.AddUObject(this, &AMyGameModeBase::MonsterClear);
		}
	}
}

void AMyGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyGameModeBase::MonsterClear()
{
	_monsterNum--;

	if (_monsterNum <= 0)
	{
		AMyPlayer *PlayerCharacter = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
		if (PlayerCharacter)
		{
			UMyStatComponent *StatComponent = PlayerCharacter->FindComponentByClass<UMyStatComponent>();
			if (StatComponent)
			{
				int32 PlayerLevel = StatComponent->GetLevel();

				UMyGameInstance *GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
				if (GameInstance)
				{
					GameInstance->SavePlayerStatus(PlayerLevel);
				}
				UGameplayStatics::OpenLevel(this, FName("BossStage"));
			}
		}
	}
}