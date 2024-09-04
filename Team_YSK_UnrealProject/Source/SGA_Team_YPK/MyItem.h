// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItem.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString ItemName;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemTexture;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* ItemMesh;

	UPROPERTY(EditAnywhere)
	int32 ItemId;

	FItemData()
		: ItemName(TEXT("Default"))
		, ItemTexture(nullptr)
		, ItemMesh(nullptr)
		, ItemId(-1)

	{}
};


UCLASS()
class SGA_TEAM_YPK_API AMyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyItem();

	void Disable();
	void Init();

	virtual void Tick(float DeltaTime) override;

	void SetItemPos(FVector pos, FRotator rot = FRotator::ZeroRotator);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 _itemId = -1;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* _meshComponent;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* _trigger;


};
