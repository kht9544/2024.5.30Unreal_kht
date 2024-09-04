// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCreature.h"
#include "MyNPC.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyNPC : public AMyCreature
{
	GENERATED_BODY()
public:
	AMyNPC();
	virtual void BeginPlay() override;
	void NPCStoreUI(bool UImark);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Store, meta = (AllowPrivateAccess = "true"))
	class UMyNPCStoreUI* _storeWidget;


};
