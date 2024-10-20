// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyMonster.h"
#include "MyBossMonster.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API AMyBossMonster : public AMyMonster
{
	GENERATED_BODY()
public:
	AMyBossMonster();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	void RandAreaAttack();

	void TargetAreaAttack(FVector target);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAggroComponent* _aggroCom;
	
private:
	virtual void Attack_AI() override;

	virtual void DropReword() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class AMyDecalActor> _decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_BossMonster_Instance* _animInstance;
};
