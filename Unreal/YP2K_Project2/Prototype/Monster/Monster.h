// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Creature.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "Monster.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMonsterDelegate);

UCLASS()
class PROTOTYPE_API AMonster : public ACreature
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void InitalizeAnim();

	UFUNCTION()
	virtual void Disable() override;
	virtual void Attack_AI();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void LaunchFromPlayer(FVector LaunchDirection);

	UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Reward();



protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics", meta = (AllowPrivateAccess = "true"))
    float _launchLength;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics", meta = (AllowPrivateAccess = "true"))
	FVector _upVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics", meta = (AllowPrivateAccess = "true"))
	class ABaseItem *_newItem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    class UCapsuleComponent* _capsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UBaseAnimInstance * _monster_AnimInstance;
	
	int32 RandomSectionIndex;

};
