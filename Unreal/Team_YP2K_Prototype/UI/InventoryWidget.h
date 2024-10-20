// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class ABaseItem;

DECLARE_MULTICAST_DELEGATE_TwoParams(ItemDropDelegate, int32 slot, bool isDrop);

UCLASS()
class PROTOTYPE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UInventoryWidget(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;

public:

	void SetItemButtons();
	void SetEquipButtons();
	void SetStats();

	void SetItemImage(int32 slotIndex, ABaseItem* item = nullptr);

	void ShowItem();

	void ExchangeEquip(int32 slotIndex);

	UFUNCTION()
	void DropItem();
	UFUNCTION()
	void UseItem();

private:
	void SetTargetItem(int32 slotIndex);
	UFUNCTION()
	void TargetItem0();
	UFUNCTION()
	void TargetItem1();
	UFUNCTION()
	void TargetItem2();
	UFUNCTION()
	void TargetItem3();
	UFUNCTION()
	void TargetItem4();
	UFUNCTION()
	void TargetItem5();
	UFUNCTION()
	void TargetItem6();
	UFUNCTION()
	void TargetItem7();
	UFUNCTION()
	void TargetItem8();
	UFUNCTION()
	void TargetItem9();
	UFUNCTION()
	void TargetItem10();
	UFUNCTION()
	void TargetItem11();

public:
	//Delegate
	ItemDropDelegate ItemDrop;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	class UTexture2D* _defaultTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Texture, meta = (AllowPrivateAccess = "true"))
	FString _defaultText;

	UPROPERTY()
	ABaseItem* _targetItem = nullptr;
	UPROPERTY()
	int32 _targetIndex = -1;

	//UI Elememts
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* ItemSlots;
	UPROPERTY(meta = (BindWidget))
	TArray<class UIndexedButton*> Button_;
	UPROPERTY(meta = (BindWidget))
	TArray<class UImage*> Image_;

	UPROPERTY(meta = (BindWidget))
	class UImage* ItemTexture;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemName;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ItemDesc;

	UPROPERTY(meta = (BindWidget))
	class UButton* DropBtn;
	UPROPERTY(meta = (BindWidget))
	class UButton* UseBtn;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* EquipSlots;
	UPROPERTY(meta = (BindWidget))
	class UButton* Helmet;
	UPROPERTY(meta = (BindWidget))
	class UButton* ShoulderGuard;
	UPROPERTY(meta = (BindWidget))
	class UButton* UpperArmor;
	UPROPERTY(meta = (BindWidget))
	class UButton* LowerArmor;
	UPROPERTY(meta = (BindWidget))
	class UButton* Sword;
	UPROPERTY(meta = (BindWidget))
	class UButton* Shield;


	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* StatSlots;
	
};
