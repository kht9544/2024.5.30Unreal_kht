// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInvenUI.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MyInvenComponent.h"
#include "MyPlayer.h"
#include "GameFramework/PlayerController.h"
#include "MyNPCItem.h"

// te
#include "Components/TextBlock.h"

void UMyInvenUI::NativeConstruct()
{

	Super::NativeConstruct();
	if (_NPCItems == nullptr)
	{
	
		_NPCItems = GetWorld()->SpawnActor<AMyNPCItem>();
	}

	auto array = SlotGrid->GetAllChildren();

	for (auto widget : array)
	{
		auto btn = Cast<UButton>(widget);
		if (btn)
		{
			_slotBtns.Add(btn);
			_slotBtnImages.Add(Cast<UImage>(btn->GetChildAt(0)));
		}

	}
	_defalut = LoadObject<UTexture2D>(nullptr, TEXT("/Script/Engine.Texture2D'/Game/Graphic/icon/Tex_DefaultTexture.Tex_DefaultTexture'"));
	

	if (DropBtn)
	{
		DropBtn->OnClicked.AddDynamic(this, &UMyInvenUI::Dropclick);
	}


	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player != nullptr && Money != nullptr)
	{
		MoneyUpdate(player->_money);
	}
}

void UMyInvenUI::SetItem(int32 itemId, int32 index)
{
	if (_slotBtnImages.IsEmpty() || !_slotBtnImages.IsValidIndex(index))
		return;

	if (itemId == -1)
	{
		_slotBtnImages[index]->SetBrushFromTexture(_defalut);
	}

	else
	{
		if (_NPCItems)
		{
			int32 DataTableIndex = itemId - 1;

			const TArray<FItemData>& Items = _NPCItems->_ItemData;
			if (Items.IsValidIndex(DataTableIndex))
			{
				UTexture2D* ItemTexture = Items[DataTableIndex].ItemTexture;
				if (ItemTexture)
				{
					_slotBtnImages[index]->SetBrushFromTexture(ItemTexture);
			
				}
				else
				{
					_slotBtnImages[index]->SetBrushFromTexture(_defalut);
				}
			}
		
		}

	}


}

void UMyInvenUI::Dropclick()
{
	AMyPlayer* player = Cast<AMyPlayer>(GetOwningPlayerPawn());
	if (player && player->_invenCom)
	{
		player->_invenCom->DropItem();
	}
}

void UMyInvenUI::MoneyUpdate(int32 newMoney)
{
	if (Money != nullptr)
	{
		Money->SetText(FText::AsNumber(newMoney));
	}
}

