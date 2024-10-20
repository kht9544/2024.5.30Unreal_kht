// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCreature.h"
#include "MyMonster.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyMonster : public AMyCreature
{
	GENERATED_BODY()
public:
	AMyMonster();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void Disable() override;

	virtual void Attack_AI(){};

protected:
	virtual void DropReword();


public:
	int32 GetExp() { return _exp; }
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	UPROPERTY(VisibleAnywhere)
	int32 _exp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	class AAIController* _aiController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ReWord, meta = (AllowPrivateAccess = "true"))
	TArray<class AMyItem*> _rewardItem;

	UPROPERTY()
	UClass* _rewardClass;

	UPROPERTY(VisibleAnywhere)
	int32 _Dropmoney;
};
