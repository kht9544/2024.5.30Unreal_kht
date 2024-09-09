// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBossGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "MyPlayer.h"
#include "MyBossMonster.h"
#include "MyBossAIController.h"
#include "MyStatComponent.h"
#include "MyAggroUserWidget.h"
#include "MyAggroComponent.h"

AMyBossGameModeBase::AMyBossGameModeBase()
{
    static ConstructorHelpers::FClassFinder<AMyBossMonster> BM(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster/MyBossMonster_BP.MyBossMonster_BP_C'"));
    if (BM.Succeeded())
    {
        _bossMonster = BM.Class;
    }

    static ConstructorHelpers::FClassFinder<UMyAggroUserWidget> AU(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MyAggroUI_BP.MyAggroUI_BP_C'"));
    if (AU.Succeeded())
    {
        _aggroUI = AU.Class;
    }
}

void AMyBossGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    UMyGameInstance *GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this));
    if (GameInstance)
    {
        AMyPlayer *PlayerCharacter = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(this, 0));
        if (PlayerCharacter)
        {
            UMyStatComponent *StatComponent = PlayerCharacter->FindComponentByClass<UMyStatComponent>();
            if (StatComponent)
            {
                int32 SavedLevel;
                GameInstance->LoadPlayerStatus(SavedLevel);
                PlayerCharacter->_statCom->SetLevelAndInit(SavedLevel);
            }
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.Name = TEXT("Boss");

        AMyBossMonster *Boss = GetWorld()->SpawnActor<AMyBossMonster>(_bossMonster, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

        if (Boss)
        {
            auto BossStatData = GameInstance->GetBossStatDataByLevel(1);
            if (BossStatData)
            {
                Boss->_statCom->SetBoss(true);
                Boss->_statCom->SetLevelAndInit(1);
            }

            AMyBossAIController *BossAI = GetWorld()->SpawnActor<AMyBossAIController>(AMyBossAIController::StaticClass());
            if (BossAI)
            {
                BossAI->Possess(Boss);
            }
        }

        if (_aggroUI)
        {
            UUserWidget *UIInstance = CreateWidget<UUserWidget>(GetWorld(), _aggroUI);
            if (UIInstance)
            {
                UMyAggroUserWidget *AggroUIWidget = Cast<UMyAggroUserWidget>(UIInstance);
                if (AggroUIWidget)
                {
                    if (Boss != nullptr)
                    {
                        Boss->_aggroCom->UpdateUI(AggroUIWidget);
                        Boss->_aggroCom->_aggroUIWidget = AggroUIWidget;
                    }
                }
                AggroUIWidget->UpdateAggroDisplay(nullptr, 0.0f);
                AggroUIWidget->AddToViewport();
            }
        }
        GameInstance->InitializeManagers();
    }
}
