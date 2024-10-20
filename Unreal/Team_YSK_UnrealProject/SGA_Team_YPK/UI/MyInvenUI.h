// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyInvenUI.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyInvenUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* SlotGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* DropBtn;

	UFUNCTION()
	void SetItem(int32 itemId, int32 index);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> _slotBtns;
	TArray<class UImage*> _slotBtnImages;

	class UTexture2D* _defalut;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	class AMyNPCItem* _NPCItems;

	UFUNCTION()
	void Dropclick();

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Money;

	void MoneyUpdate(int32 newMoney);

};
