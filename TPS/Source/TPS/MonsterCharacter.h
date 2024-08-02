// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyInventoryComponent.h"
#include "MonsterCharacter.generated.h"

UCLASS()
class TPS_API AMonsterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSubclassOf<UAnimInstance> AnimBlueprint;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	void Dead();

	void AddItem(class AMyItem* item);

	void StartItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isDead = false;

	//Animation
	class UMonsterAnimInstance* _monsteranimInstance;

protected:
	UPROPERTY(VisibleAnywhere, Category = Stat)
	float _curHp = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float _maxHp = 500.0f;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	float _attackDamage = 50.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UMyInventoryComponent* _InventoryCom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = item)
	TSubclassOf<AMyItem> _myItem ;



};
