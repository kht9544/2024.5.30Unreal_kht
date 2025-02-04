// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyItem.h"
#include "MyNPCItem.h"
#include "MyInvenComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(ItemAdded, int itemId, int itemIndex)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAM_YPK_API UMyInvenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyInvenComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void AddItem(AMyNPCItem* item);
	UFUNCTION()
	void DropItem(); 
	void AllDropItem(); 
	void SetMoney(int32 money){_money = money;}
	void AddMoney(int32 money){SetMoney(_money+money);}
	ItemAdded _itemAddedEvent;
	int GetMoney(){ return _money; }
	

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TArray<class AMyNPCItem*> _items;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	int32 _money;
};
