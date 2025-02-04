// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMonster.h"
#include "MyBaseMonster.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyBaseMonster : public AMyMonster
{
	GENERATED_BODY()
public:
	AMyBaseMonster();

	virtual void Attack_AI() override;
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	virtual FString GetHitParticleName() const override;
	virtual FString GetHitSoundName() const override;
	virtual FString GetDeadSoundName() const override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_Monster_Instance* _animInstance;
	

};
