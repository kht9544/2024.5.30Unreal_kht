// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameModeBase.h"
#include "../Component/StatComponent.h"
#include "MyGameInstance.h"
#include "../Player/MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "UI/SkillWidget_test.h"
#include "../Player/MyPlayer.h"
#include "../Player/Portal/Portal_Stage2_Normal.h"
#include "../Monster/NormalMonster.h"
#include "../Monster/AI/AIController_NormalMonster.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Kismet/GameplayStatics.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APortal_Stage2_Normal> PS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/Portal/Stage2Normal_Portal_BP.Stage2Normal_Portal_BP_C'"));
	if (PS.Succeeded())
	{
		_portal2 = PS.Class;
	}

	static ConstructorHelpers::FClassFinder<ANormalMonster> NM(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/NormalMonster/BaseMap_NormalMonster_03_BP.BaseMap_NormalMonster_03_BP_C'"));
	if (NM.Succeeded())
	{
		_monster = NM.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Dragon_UI.Dragon_UI_C'"));
	if (UW.Succeeded())
	{
		_dragonUI = UW.Class;
	}
	
}

void AMyGameModeBase::BeginPlay()
{
	AMyPlayer *player = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		UStatComponent *StatComponent = player->FindComponentByClass<UStatComponent>();
		UInventoryComponent *InvenComponent = player->FindComponentByClass<UInventoryComponent>();
		UMyGameInstance *GameInstance = Cast<UMyGameInstance>(GetGameInstance());

		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyGameModeBase::LockSkill, 0.1f, false);

		if (GameInstance)
		{
			if (GameInstance->GetFirst())
			{
				GameInstance->InitializeManagers();
				
				if (StatComponent)
				{
					player->_StatCom->SetLevelInit(1);
				}
				if (InvenComponent)
				{
					player->GetInventory()->InitSlot();
				}

				FVector BaseLocation(-4120.f, -3620.f, 18.f);
				FVector AddLocation(-300.f,1200.f,0.0f);
				SpawnMonster(BaseLocation,AddLocation);

				GameInstance->SetFirst(false);
			}
			else
			{
				GameInstance->InitializeManagers();
				
				if (StatComponent)
				{
					GameInstance->LoadPlayerStats(StatComponent);
				}
				if (InvenComponent)
				{
					GameInstance->LoadInventory(InvenComponent);
				}
				GameInstance->LoadPlayerSkeletal(player);
				player->_StatCom->Reset();

				if (GameInstance->GetStage1Clear())
				{
					FVector BaseLocation(1310.f, 50.f, 18.f);
					FVector AddLocation(500.f,830.f,0.0f);
					SpawnMonster(BaseLocation,AddLocation);
					if (_portal2)
					{
						FVector Location(5690.f, 5900.f, -40.f);
						FRotator Rotation(0.f, 0.f, 0.f);
						GetWorld()->SpawnActor<APortal_Stage2_Normal>(_portal2, Location, Rotation);
					}
				}

				if(GameInstance->GetStage2Clear())
				{
					ShowDragonUI();
				}

			}
		}
	}
}

void AMyGameModeBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMyGameModeBase::LockSkill()
{
	AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController && PlayerController->SkillWidgetInstance)
	{
		PlayerController->SkillWidgetInstance->LockAllSkill();
	}
}

void AMyGameModeBase::ShowDragonUI()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && _dragonUI)
    {
        UUserWidget* DragonWidget = CreateWidget<UUserWidget>(PlayerController, _dragonUI);
        if (DragonWidget)
        {
            DragonWidget->AddToViewport();

            FTimerHandle TimerHandle;
            GetWorldTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([DragonWidget]() {
                DragonWidget->RemoveFromViewport();
            }), 5.0f, false);
        }
    }
}

void AMyGameModeBase::SpawnMonster(FVector BaseLocation, FVector AddLocation)
{
	if (_monster)
    {
        FActorSpawnParameters SpawnParams;
        for (int i = 0; i < 5; ++i) 
        {
            SpawnParams.Name = FName(*FString::Printf(TEXT("Monster_%d"), i + 1));
            
            FVector SpawnLocation = BaseLocation + (AddLocation * i);
            
            ANormalMonster* Monster = GetWorld()->SpawnActor<ANormalMonster>(_monster, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
            if (Monster)
            {
                Monster->_StatCom->SetMonsterLevelInit(1);
                AAIController_NormalMonster* MonsterAI = GetWorld()->SpawnActor<AAIController_NormalMonster>(AAIController_NormalMonster::StaticClass());
                if (MonsterAI)
                {
                    MonsterAI->OnPossess(Monster);
                }
            }
        }
    }
}

