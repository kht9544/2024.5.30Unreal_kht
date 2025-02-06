// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/Managers/UIManager.h"

#include "UI/StatWidget.h"
#include "UI/InventoryWidget.h"
#include "UI/Boss1Widget.h"
#include "UI/Boss2Widget.h"
#include "UI/ShopWidget.h"
#include "UI/MainStartWidget.h"
#include "UI/SkillWidget.h"
#include "UI/PlayerBarWidget.h"
#include "Kismet/GameplayStatics.h"

#include "TriggerBox_StageSequnce/StageSequence_Trigger.h"

// Sets default values
AUIManager::AUIManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> inventory(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory_UI.Inventory_UI_C'"));
	if (inventory.Succeeded())
	{
		_inventoryUI = CreateWidget<UInventoryWidget>(GetWorld(), inventory.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> stat(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerStat_UI.PlayerStat_UI_C'"));
	if (stat.Succeeded())
	{
		_statUI = CreateWidget<UStatWidget>(GetWorld(), stat.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> boss1widget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Boss_UI.Boss_UI_C'"));
	if (boss1widget.Succeeded())
	{
		_bossUI = CreateWidget<UBoss1Widget>(GetWorld(), boss1widget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> boss2widget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Boss2_UI.Boss2_UI_C'"));
	if (boss2widget.Succeeded())
	{
		_boss2UI = CreateWidget<UBoss2Widget>(GetWorld(), boss2widget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> shopUI(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Shop_UI.Shop_UI_C'"));
	if (shopUI.Succeeded())
	{
		_shopUI = CreateWidget<UShopWidget>(GetWorld(), shopUI.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> StartWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MainStart_UI.MainStart_UI_C'"));
	if (StartWidget.Succeeded())
	{
		_startUI = CreateWidget<UMainStartWidget>(GetWorld(), StartWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> LoadWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Widget_Info.Widget_Info_C'"));
	if (LoadWidget.Succeeded())
	{
		_loadUI = CreateWidget<UUserWidget>(GetWorld(), LoadWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> OptionsWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/options_UITEST.options_UITEST_C'"));
	if (OptionsWidget.Succeeded())
	{
		_options = CreateWidget<UUserWidget>(GetWorld(), OptionsWidget.Class);
	}

	static ConstructorHelpers::FObjectFinder<UTexture2D> defaultTexture(
		TEXT("/Script/Engine.Texture2D'/Game/CraftResourcesIcons/Textures/T_Default.T_Default'"));
	if (defaultTexture.Succeeded())
	{
		_defaultTexture = defaultTexture.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SkillWidget(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Skill_UI.Skill_UI_C'"));
	if (SkillWidget.Succeeded())
	{
		_skillUI = CreateWidget<USkillWidget>(GetWorld(), SkillWidget.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlBar(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerBar_UI.PlayerBar_UI_C'"));
	if (PlBar.Succeeded())
	{
		_playerBarUI = CreateWidget<UPlayerBarWidget>(GetWorld(), PlBar.Class);
	}

	_uiList = {_inventoryUI, _statUI, _bossUI, _boss2UI, _shopUI, _startUI, _loadUI, _options, _skillUI, _playerBarUI};
	_uiIsOpen.Init(false, _uiList.Num());
	_isPauseWhenOpen.Init(true, _uiList.Num());
}

void AUIManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIManager::OpenUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;

	if (UIindex > _uiList.Num())
		return;

	if (InventoryMutual(ui) || InterectMutual(ui))
		return;

	if (_isPauseWhenOpen[UIindex])
		pauseGame.Broadcast();

	if (ui == UI_LIST::Inventory || ui == UI_LIST::Shop || ui == UI_LIST::Options || ui == UI_LIST::Stat)
	{
		cnt++;
	}

	APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && cnt > 0)
	{
		bool bIsCursorVisible = PlayerController->bShowMouseCursor;
		PlayerController->bShowMouseCursor = true;
		PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
	}

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Visible);
	static int32 LastZOrder = 0;
	LastZOrder++;
	_uiList[UIindex]->AddToViewport(LastZOrder);

	_uiIsOpen[UIindex] = true;
}

void AUIManager::CloseUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (_isPauseWhenOpen[UIindex])
		resumGame.Broadcast();

	if (ui == UI_LIST::Inventory || ui == UI_LIST::Shop || ui == UI_LIST::Options || ui == UI_LIST::Stat)
	{
		cnt--;
	}

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Hidden);
	_uiList[UIindex]->RemoveFromParent();

	_uiIsOpen[UIindex] = false;

	if (cnt == 0)
	{
		APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}

void AUIManager::CloseAll()
{
	resumGame.Broadcast();

	for (auto widget : _uiList)
	{
		if (widget)
		{
			widget->SetVisibility(ESlateVisibility::Hidden);
			widget->RemoveFromParent();
		}
	}
	for (bool isopen : _uiIsOpen)
		isopen = false;
}

void AUIManager::ToggleUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (_uiIsOpen[UIindex])
		CloseUI(ui);
	else
		OpenUI(ui);
}

void AUIManager::SetPlayerUI(UStatComponent* StatCom)
{
	if(StatCom == nullptr)
		return;
	
	float CurrentHP = StatCom->GetCurHp();
	float CurrentMP = StatCom->GetCurMp();
	float CurrentEXP = StatCom->GetExp();

	StatCom->_PlHPDelegate.AddUObject(_playerBarUI, &UPlayerBarWidget::SetPlHPBar);
	StatCom->_PlMPDelegate.AddUObject(_playerBarUI, &UPlayerBarWidget::SetPlMPBar);
	StatCom->_PlEXPDelegate.AddUObject(_playerBarUI, &UPlayerBarWidget::SetPlExpBar);
	StatCom->_PlMaxHPDelegate.AddUObject(_playerBarUI, &UPlayerBarWidget::SetMaxHpBar);
	StatCom->_PlMaxMPDelegate.AddUObject(_playerBarUI, &UPlayerBarWidget::SetMaxMpBar);

}

bool AUIManager::InventoryMutual(UI_LIST invenUI)
{
	if (invenUI != UI_LIST::Inventory)
		return false;
	if (_uiIsOpen[(int32)UI_LIST::Shop])
		return true;
	return false;
}

bool AUIManager::InterectMutual(UI_LIST interectUI)
{
	if (interectUI != UI_LIST::Shop)
		return false;
	if (_uiIsOpen[(int32)UI_LIST::Inventory])
		return true;
	return false;
}
