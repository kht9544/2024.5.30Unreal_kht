// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/Stage1BossGameModeBase.h"
#include "../Component/StatComponent.h"
#include "../Component/InventoryComponent.h"
#include "../Player/Portal/Portal_Home.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../Player/MyPlayerController.h"
#include "../Base/Managers/UIManager.h"
#include "../Monster/BossMonster.h"
#include "../Monster/AI/AIController_BossMonster.h"
#include "UI/Boss1Widget.h"
#include "UI/SkillWidget.h"
#include "Kismet/GameplayStatics.h"

AStage1BossGameModeBase::AStage1BossGameModeBase()
{
	static ConstructorHelpers::FClassFinder<ABossMonster> BM(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/BossMonster/BossMonster_BP.BossMonster_BP_C'"));
	if (BM.Succeeded())
	{
		_boss = BM.Class;
	}

	static ConstructorHelpers::FClassFinder<APortal_Home> PH(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/Portal/HomePortal_BP.HomePortal_BP_C'"));
	if (PH.Succeeded())
	{
		_portal = PH.Class;
	}
}

void AStage1BossGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FTimerHandle TimerHandle;
        GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([this]()
        {
            if (UIManager && UIManager->GetSkillUI())
            {
                UIManager->GetSkillUI()->LockAllSkill();
            }
        }), 0.1f, false);

		UMyGameInstance *GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			GameInstance->InitializeManagers();
			UStatComponent *StatComponent = player->FindComponentByClass<UStatComponent>();
			if (StatComponent)
			{
				GameInstance->LoadPlayerStats(StatComponent);
			}

			UInventoryComponent *InvenComponent = player->FindComponentByClass<UInventoryComponent>();
			if (InvenComponent)
			{
				GameInstance->LoadInventory(InvenComponent);
			}
			GameInstance->LoadPlayerSkeletal(player);
		}

		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AStage1BossGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AStage1BossGameModeBase::BossClear()
{
	GAMEINSTANCE->SetStage1Clear(true);
	if (_portal)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = TEXT("PortalHome");

		FVector PortalLocation = FVector(-8270.0f, 210.0f, 100.0f);
		FRotator PortalRotation = FRotator::ZeroRotator;

		APortal_Home *Portal = GetWorld()->SpawnActor<APortal_Home>(_portal, PortalLocation, PortalRotation, SpawnParams);
	}
}

void AStage1BossGameModeBase::BossStart()
{
	UIManager->OpenUI(UI_LIST::Boss);
	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		FVector NewLocation = FVector(-5202.5f, 12.0f, 150.f);
		FRotator NewRotation = FRotator::ZeroRotator;

		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
		UIManager->GetSkillUI()->UnLockAllSkill();
		player->SetActorLocationAndRotation(NewLocation, NewRotation);
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = TEXT("Boss");

	ABossMonster *Boss = GetWorld()->SpawnActor<ABossMonster>(_boss, FVector(-7787.8f, -191.5f, 171.1f), FRotator::ZeroRotator, SpawnParams);
	if (Boss)
	{
		Boss->GetStatComponent()->SetBossLevelInit(1);
		AAIController_BossMonster *BossAI = GetWorld()->SpawnActor<AAIController_BossMonster>(AAIController_BossMonster::StaticClass());
		if (BossAI)
		{
			BossAI->OnPossess(Boss);
		}

		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}

		Boss->GetStatComponent()->_PlHPDelegate.AddUObject(UIManager->GetBossUI(), &UBoss1Widget::UpdateBossHPBar);
		Boss->GetStatComponent()->_deathDelegate.AddUObject(this, &AStage1BossGameModeBase::BossClear);
	}
}
