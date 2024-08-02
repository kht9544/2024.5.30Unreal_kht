// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyStatComponent.h"
#include "MyInventoryUI.h"
#include "MyInventoryComponent.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyStatData* GetStatDataByLevel(int level);



private:
	UPROPERTY()
	class UDataTable* _statTable;
};
