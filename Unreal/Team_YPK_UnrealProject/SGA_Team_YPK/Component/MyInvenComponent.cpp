// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenComponent.h"
#include "MyItem.h"
#include "MyPlayer.h"
#include "MyInvenUI.h"
#include "MyNPCItem.h"

UMyInvenComponent::UMyInvenComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;


}


void UMyInvenComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AMyPlayer* player = Cast<AMyPlayer>(GetOwner());
	if (player && player->_invenWidget)
	{
		_itemAddedEvent.AddUObject(player->_invenWidget, &UMyInvenUI::SetItem);
	}
}


void UMyInvenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyInvenComponent::AddItem(AMyNPCItem* item)
{
	_items.Add(item);
	_itemAddedEvent.Broadcast(item->_itemId, _items.Num() - 1);

}

void UMyInvenComponent::DropItem()
{
	if (_items.Num() == 0)
		return;

	int itemSize = _items.Num();
	auto item = _items.Pop();
	_itemAddedEvent.Broadcast(-1, itemSize - 1);

	float randFloat = FMath::FRandRange(0, PI * 2.0f);
	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetOwner()->GetActorLocation();
	playerPos.Z = 0.0f;
	FVector itemPos = playerPos + FVector(X, Y, 0.0f);

	item->SetItemPos(itemPos);


}

void UMyInvenComponent::AllDropItem()
{
	if (_items.Num() > 0)
	{
		TArray<AMyNPCItem*> ItemsToDrop = _items;

		for (auto item : ItemsToDrop)
		{
			if (item)
			{
				float randFloat = FMath::FRandRange(0, PI * 2.0f);
				float X = cosf(randFloat) * 300.0f;
				float Y = sinf(randFloat) * 300.0f;
				FVector playerPos = GetOwner()->GetActorLocation();
				playerPos.Z = GetOwner()->GetActorLocation().Z;
				FVector itemPos = playerPos + FVector(X, Y, 0.0f);

				item->SetItemPos(itemPos);
				item->Init();
				
				_items.Remove(item);
			}
		}
	}
}
