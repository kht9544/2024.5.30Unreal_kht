// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/StatWidget.h"

#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Player/MyPlayer.h"
#include "Components/TextBlock.h"

void UStatWidget::NativeConstruct()
{

	Super::NativeConstruct();

	auto array = SlotGrid->GetAllChildren();

	for (auto widget : array)
	{
		auto btn = Cast<UButton>(widget);
		if (btn)
		{
			_slotBtns.Add(btn);
			_slotBtnText.Add(Cast<UTextBlock>(btn->GetChildAt(0)));
		}
	}

	if (HPUp)
	{
		HPUp->OnClicked.AddDynamic(this, &UStatWidget::HPUpClick);
	}

	if (MPUp)
	{
		MPUp->OnClicked.AddDynamic(this, &UStatWidget::MpUpClick);
	}

	if (STRUp)
	{
		STRUp->OnClicked.AddDynamic(this, &UStatWidget::STRUpClick);
	}
	if (DEXUp)
	{
		DEXUp->OnClicked.AddDynamic(this, &UStatWidget::DEXUpClick);
	}
	if (INTUp)
	{
		INTUp->OnClicked.AddDynamic(this, &UStatWidget::INTUpClick);
	}

	if (HPDown)
	{
		HPDown->OnClicked.AddDynamic(this, &UStatWidget::HPDownClick);
	}

	if (MPDown)
	{
		MPDown->OnClicked.AddDynamic(this, &UStatWidget::MPDownClick);
	}

	if (STRDown)
	{
		STRDown->OnClicked.AddDynamic(this, &UStatWidget::STRDownClick);
	}

	if (DEXDown)
	{
		DEXDown->OnClicked.AddDynamic(this, &UStatWidget::DEXDownClick);
	}

	if (INTDown)
	{
		INTDown->OnClicked.AddDynamic(this, &UStatWidget::INTDownClick);
	}
	UpdateStatDisplay();
}

void UStatWidget::StatUpdate(StatType type, int amount)
{
	switch (type)
	{
	case StatType::HP:
		HPNum->SetText(FText::AsNumber(amount));
		break;
	case StatType::MP:
		MPNum->SetText(FText::AsNumber(amount));
		break;
	case StatType::STR:
		STRNum->SetText(FText::AsNumber(amount));
		break;
	case StatType::DEX:
		DEXNum->SetText(FText::AsNumber(amount));
		break;
	case StatType::INT:
		INTNum->SetText(FText::AsNumber(amount));
		break;
	default:
		break;
	}
}

void UStatWidget::PlLevelUpdate(int32 Level)
{
	if (PlLevel)
	{
		PlLevel->SetText(FText::AsNumber(Level));
	}
}

void UStatWidget::HPUpdate(int32 HP)
{
	if (HPNum)
	{
		HPNum->SetText(FText::AsNumber(HP));
	}
}

void UStatWidget::MPUpdate(int32 MP)
{
	if (MPNum != nullptr)
	{
		MPNum->SetText(FText::AsNumber(MP));
	}
}

void UStatWidget::STRUpdate(int32 STR)
{
	if (STRNum != nullptr)
	{
		STRNum->SetText(FText::AsNumber(STR));
	}
}

void UStatWidget::DEXUpdate(int32 DEX)
{
	if (DEXNum != nullptr)
	{
		DEXNum->SetText(FText::AsNumber(DEX));
	}
}

void UStatWidget::INTUpdate(int32 INT)
{
	if (INTNum != nullptr)
	{
		INTNum->SetText(FText::AsNumber(INT));
	}
}

void UStatWidget::BonusPointUpdate(int32 BonusPoint)
{
	if (BonusNum != nullptr)
	{
		BonusNum->SetText(FText::AsNumber(BonusPoint));
	}
}

void UStatWidget::UpdateStatDisplay()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		HPUpdate(player->GetStatComponent()->GetMaxHp());
		MPUpdate(player->GetStatComponent()->GetMaxMp());
		STRUpdate(player->GetStatComponent()->GetStr());
		DEXUpdate(player->GetStatComponent()->GetDex());
		INTUpdate(player->GetStatComponent()->GetInt());

		BonusPointUpdate(player->GetStatComponent()->GetBonusPoint());
		PlLevelUpdate(player->GetStatComponent()->GetLevel());
	}
}

void UStatWidget::HPDownClick()
{

	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatHp = player->GetStatComponent()->GetMaxHp();
		int32 baseHp = player->GetStatComponent()->GetCurHp();
		int32 bonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (StatHp > baseHp)
		{
			player->GetStatComponent()->SetMaxHp(StatHp - 100);
			player->GetStatComponent()->SetBonusPoint(bonusPoints + 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::HPUpClick()
{

	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatHp = player->GetStatComponent()->GetMaxHp();
		int32 BonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->GetStatComponent()->SetMaxHp(StatHp + 100);
			player->GetStatComponent()->SetBonusPoint(BonusPoints - 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::MPDownClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatMp = player->GetStatComponent()->GetMaxMp();
		int32 baseHp = player->GetStatComponent()->GetCurMp();
		int32 bonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (StatMp > baseHp)
		{
			player->GetStatComponent()->SetMaxMp(StatMp - 10);
			player->GetStatComponent()->SetBonusPoint(bonusPoints + 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::MpUpClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatMp = player->GetStatComponent()->GetMaxMp();
		int32 BonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->GetStatComponent()->SetMaxMp(StatMp + 10);
			player->GetStatComponent()->SetBonusPoint(BonusPoints - 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::STRDownClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatStr = player->GetStatComponent()->GetStr();
		int32 bonusPoints = player->GetStatComponent()->GetBonusPoint();

		player->GetStatComponent()->SetStr(StatStr - 1);
		player->GetStatComponent()->SetBonusPoint(bonusPoints + 1);
		
		UpdateStatDisplay();
	}
}

void UStatWidget::STRUpClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatStr = player->GetStatComponent()->GetStr();
		int32 BonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (BonusPoints > 0)
		{
			player->GetStatComponent()->SetStr(StatStr + 1);
			player->GetStatComponent()->SetBonusPoint(BonusPoints - 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::DEXDownClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatDex = player->GetStatComponent()->GetDex();
		int32 bonusPoints = player->GetStatComponent()->GetBonusPoint();

		player->GetStatComponent()->SetDex(StatDex - 1);
		player->GetStatComponent()->SetBonusPoint(bonusPoints + 1);

		UpdateStatDisplay();
	}
}

void UStatWidget::DEXUpClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatDex = player->GetStatComponent()->GetDex();
		int32 StatBonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (StatBonusPoints > 0)
		{
			player->GetStatComponent()->SetDex(StatDex + 1);
			player->GetStatComponent()->SetBonusPoint(StatBonusPoints - 1);
		}
		UpdateStatDisplay();
	}
}

void UStatWidget::INTDownClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatInt = player->GetStatComponent()->GetInt();
		int32 bonusPoints = player->GetStatComponent()->GetBonusPoint();

		player->GetStatComponent()->SetInt(StatInt - 1);
		player->GetStatComponent()->SetBonusPoint(bonusPoints + 1);
		
		UpdateStatDisplay();
	}
}

void UStatWidget::INTUpClick()
{
	AMyPlayer *player = Cast<AMyPlayer>(GetOwningPlayerPawn());

	if (player && player->GetStatComponent())
	{
		int32 StatInt = player->GetStatComponent()->GetInt();
		int32 StatBonusPoints = player->GetStatComponent()->GetBonusPoint();

		if (StatBonusPoints > 0)
		{
			player->GetStatComponent()->SetInt(StatInt + 1);
			player->GetStatComponent()->SetBonusPoint(StatBonusPoints - 1);
		}
		UpdateStatDisplay();
	}
}
