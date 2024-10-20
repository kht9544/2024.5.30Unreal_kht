// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyNPCStoreUI.generated.h"

/**
 *
 */

UCLASS()
class SGA_TEAM_YPK_API UMyNPCStoreUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* NPCSlotGrid;

	UPROPERTY(meta = (BindWidget))
	class UButton* BuyBtn;

	UPROPERTY(meta = (BindWidget))
	class UButton* NPCSlotBtn_1;
	UPROPERTY(meta = (BindWidget))
	class UButton* NPCSlotBtn_2;
	UPROPERTY(meta = (BindWidget))
	class UButton* NPCSlotBtn_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class UButton*> _NPCslotBtns;
	TArray<class UImage*> _NPCslotBtnImages;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<struct FItemData> _Items;
	
	class AMyNPCItem* npItem;

	void SetNPCItems(const TArray<FItemData>& Items);

	UFUNCTION()
	void Buyclick(); 	 

	UFUNCTION()
	void checkbtn1();

	UFUNCTION()
	void checkbtn2();

	UFUNCTION()
	void checkbtn3();

	class AMyPlayer* Player;

	bool butncheck = false;

	int32 SelectedItemIndex = -1;


	UPROPERTY(meta = (BindWidget))
	UImage* ItemImage;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Name;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemPrice;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemAtk;

	void SelectItem(int32 Item);
private:



}; 
