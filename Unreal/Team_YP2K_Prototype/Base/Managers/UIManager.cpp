// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/Managers/UIManager.h"

#include "UI/InventoryWidget.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	static ConstructorHelpers::FClassFinder<UUserWidget> inventory(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Inventory_UI.Inventory_UI_C'")
	);
	if (inventory.Succeeded())
	{
		_inventoryUI = CreateWidget<UInventoryWidget>(GetWorld(), inventory.Class);
	}

	_uiList.Add(_inventoryUI);
	_uiIsOpen.Add(false);
	_isPauseWhenOpen.Add(true);
}

// Called when the game starts or when spawned
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

	if (_isPauseWhenOpen[UIindex])
		pauseGame.Broadcast();

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Visible);
	_uiList[UIindex]->AddToViewport(UIindex);
	_uiIsOpen[UIindex] = true;
}

void AUIManager::CloseUI(UI_LIST ui)
{
	int32 UIindex = (int32)ui;
	if (UIindex > _uiList.Num())
		return;

	if (_isPauseWhenOpen[UIindex])
		resumGame.Broadcast();

	_uiList[UIindex]->SetVisibility(ESlateVisibility::Hidden);
	_uiList[UIindex]->RemoveFromParent();
	_uiIsOpen[UIindex] = false;
}

void AUIManager::CloseAll()
{
	resumGame.Broadcast();

	for (auto widget : _uiList)
	{
		widget->SetVisibility(ESlateVisibility::Hidden);
		widget->RemoveFromParent();
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

