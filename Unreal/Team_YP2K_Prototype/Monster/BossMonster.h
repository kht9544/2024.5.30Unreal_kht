// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/Monster.h"
#include "BossMonster.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ABossMonster : public AMonster
{
	GENERATED_BODY() 
	
public:
	// Sets default values for this character's properties
	ABossMonster();

	bool PerformGimmick();

	void SetCanTeleport(bool CanTel){_CanTeleport = CanTel;}
	

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	bool _CanTeleport = false;
};
