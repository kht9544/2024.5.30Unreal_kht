// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyNPCItem.h"
#include "MyNPCStoreComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAM_YPK_API UMyNPCStoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyNPCStoreComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Items, meta = (AllowPrivateAccess = "true"))
	TArray<class AMyNPCItem*> _Npcitems;

	void AddStoreItem(AMyNPCItem* newitem);


protected:

};
