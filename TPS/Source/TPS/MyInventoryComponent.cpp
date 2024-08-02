// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInventoryComponent.h"
#include "MyCharacter.h"
#include "MyGameModeBase.h"
#include "Components/WidgetComponent.h"
#include "MyItem.h"

// Sets default values for this component's properties
UMyInventoryComponent::UMyInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMyInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	// ...
	
}


// Called every frame
void UMyInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMyInventoryComponent::LogItem()
{
	if (_items.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Empty"));
	}
	else 
	{
		for (auto i : _items)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory item : %s"), *(i->GetName()));
		}

	}



}

void UMyInventoryComponent::DropItem(FVector dropPos)
{

	if (_items.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ieventory Empty"));
		return;
	}
		
	UE_LOG(LogTemp, Log, TEXT("Item Drop"));

	auto item = _items.Pop();

	item->SetItemPos(dropPos);
}

void UMyInventoryComponent::AddItem(AMyItem* item)
{
	_items.Add(item);
}

void UMyInventoryComponent::CloseInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("Close Inventory"));
	if (GameModeBase != nullptr)
	{
		GameModeBase->InventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMyInventoryComponent::OpenInventory()
{
	UE_LOG(LogTemp, Warning, TEXT("Open Inventory"));
	if(GameModeBase != nullptr)
	{
		GameModeBase->InventoryWidgetInstance->SetVisibility(ESlateVisibility::Visible);
	}
	
}


