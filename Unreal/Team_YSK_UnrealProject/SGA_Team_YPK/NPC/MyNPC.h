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

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Store, meta = (AllowPrivateAccess = "true"))
	class UMyNPCStoreUI* _storeWidget;

	void Attack_AI() ;

	void WeaponMove();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_Monster_Instance* _animInstance;

	class AMyWeapon* CurWeapon;
protected:
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
	class AAIController* _aiController;
};
