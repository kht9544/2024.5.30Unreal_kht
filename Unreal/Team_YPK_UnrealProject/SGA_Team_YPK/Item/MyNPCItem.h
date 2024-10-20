// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyItem.h"
#include "MyNPCItem.generated.h"

/**
 * 
 */


UCLASS()
class SGA_TEAM_YPK_API AMyNPCItem : public AMyItem
{
	GENERATED_BODY()

public:	
	AMyNPCItem();
	virtual void BeginPlay();

	virtual void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item")
	TArray<FItemData> _ItemData;
	
private:
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	UTexture2D* GetItemTexture() const;
	UDataTable* ItemDataTable;
	FItemData* ItemRow;

	void InitializeItem(int32 ItemId);


	UPROPERTY(EditAnywhere, Category = "Item")
	FDataTableRowHandle ItemRowHandle;

};
