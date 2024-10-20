// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/InventoryComponent.h"

#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"

#include "Item/BaseItem.h"
#include "Item/Equip/Helmet.h"
#include "Item/Equip/UpperArmor.h"
#include "Item/Equip/ShoulderGuard.h"
#include "Item/Equip/LowerArmor.h"
#include "Item/Equip/Sword.h"
#include "Item/Equip/Shield.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	_ItemSlots.Init(nullptr, _itemSlotMax);
	_EquipSlots.Add(TEXT("Helmet"));
	_EquipSlots.Add(TEXT("UpperArmor"));
	_EquipSlots.Add(TEXT("ShoulderGuard"));
	_EquipSlots.Add(TEXT("LowerArmor"));
	_EquipSlots.Add(TEXT("Sword"));
	_EquipSlots.Add(TEXT("Shield"));
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SlotFullCheck()
{
	for (int i = 0; i < _itemSlotMax; i++)
	{
		if (_ItemSlots[i] == nullptr)
		{
			_isSlotFull = false;
			return;
		}
	}
	_isSlotFull = true;
}

void UInventoryComponent::TryEquip(FString part, int32 slot)
{
	// if there is already filled, exchange each.
}

void UInventoryComponent::AddItem(int32 slot, ABaseItem *item)
{
	if (item == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;
	if (_isSlotFull)
		return;
	// Fill into EmptySlot First
	if (!_EmptySlots.IsEmpty())
	{
		int32 emptyslot;
		_EmptySlots.HeapPop(emptyslot, true);
		SlotFullCheck();
		UIupdate_Add(emptyslot, item);
		return;
	}
	// Fill into Selected Slot
	if (_ItemSlots[slot] == nullptr)
	{
		_ItemSlots[slot] = item;
		UIupdate_Add(slot, item);
		SlotFullCheck();
	}
	// if Already filled, fill into next slot
	else
	{
		for (int i = slot; i < _itemSlotMax; i++)
		{
			if (_ItemSlots[i] != nullptr)
				continue;
			_ItemSlots[i] = item;
			UIupdate_Add(i, item);
			SlotFullCheck();
			return;
		}
		return;
	}
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UIManager->GetInventoryUI()->ItemDrop.AddUObject(this, &UInventoryComponent::ExcuteItem);
}

void UInventoryComponent::ExcuteItem(int32 slot, bool isDrop)
{
	if (_ItemSlots[slot] == nullptr)
		return;
	if (slot >= _itemSlotMax)
		return;

	FVector playerPlos = GetOwner()->GetActorLocation();

	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector itemPos = playerPlos + FVector(X, Y, 0.0f);
	itemPos.Z = 50.0f;

	UIupdate_Pop(slot);

	if (isDrop)
		_ItemSlots[slot]->DropItem(itemPos);
	else
		_ItemSlots[slot]->UseItem();

	_ItemSlots[slot] = nullptr;
	_EmptySlots.Add(slot);
}

void UInventoryComponent::EquipItem(int32 slot)
{
	// TODO : Switch-case with EquipType Enum later
	auto equipment = Cast<AHelmet>(_ItemSlots[slot]);
	if (equipment != nullptr)
	{
		TryEquip(TEXT("Helmet"), slot);
		return;
	}
}

void UInventoryComponent::UIupdate_Add(int32 slot, ABaseItem *item)
{
	UIManager->GetInventoryUI()->SetItemImage(slot, item);
}

void UInventoryComponent::UIupdate_Pop(int32 slot)
{
	UIManager->GetInventoryUI()->SetItemImage(slot, nullptr);
}

void UInventoryComponent::UIupdate_equip(int32 slot, ABaseItem *item)
{
}
