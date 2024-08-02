// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyGameModeBase();

	virtual void BeginPlay() override;

	UPROPERTY()
	UClass* _monsterClass;

	UPROPERTY()
	UUserWidget* InventoryWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _jumpWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _inventoryWidget;

	UPROPERTY()
	TArray<class AMonsterCharacter*> _monsters;
};
