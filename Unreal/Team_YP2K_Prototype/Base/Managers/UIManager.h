// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

UENUM()
enum class UI_LIST
{
	Inventory,

};

DECLARE_MULTICAST_DELEGATE(PAUSE_GAME);
DECLARE_MULTICAST_DELEGATE(RESUM_GAME);

class UInventoryWidget;
UCLASS()
class PROTOTYPE_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenUI(UI_LIST ui);
	void CloseUI(UI_LIST ui);
	void CloseAll();
	void ToggleUI(UI_LIST ui);

	UInventoryWidget* GetInventoryUI() { return _inventoryUI; }


	PAUSE_GAME pauseGame;
	RESUM_GAME resumGame;
private:
	UPROPERTY()
	TArray<UUserWidget*> _uiList;

	UPROPERTY()
	TArray<bool> _uiIsOpen;

	UPROPERTY()
	TArray<bool> _isPauseWhenOpen;

	UPROPERTY()
	UInventoryWidget* _inventoryUI;
};
