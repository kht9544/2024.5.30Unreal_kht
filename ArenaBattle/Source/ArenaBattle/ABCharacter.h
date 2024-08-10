// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattle.h"
#include "GameFramework/Character.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "ABCharacter.generated.h"



UCLASS()
class ARENABATTLE_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	enum class EControlMode
	{
		GTA,
		DIABLO
	};

	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove = FVector::ZeroVector;

	float ArmLengthTo = 0.0F;
	FRotator ArmRotationTo = FRotator::ZeroRotator;
	float ArmLengthSpeed = 0.0f;
	float ArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CanSetWeapon();
	void SetWeapon(class AABWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	class AABWeapon* CurrentWeapon;

	UPROPERTY(VisibleAnywhere, Category="Stat")
	class UABCharacterStatComponent* CharacterStat;

	UPROPERTY(VisibleAnywhere,Category="Camera")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere,Category="UI")
	class UWidgetComponent* HPBarWidget;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Attack",Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(VisibleAnywhere,Category="Weapon")
	USkeletalMeshComponent* Weapon;
	
	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack", Meta = (AllowPrivateAccess = true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack", Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack", Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly,Category="Attack", Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack", Meta = (AllowPrivateAccess = true))
	float AttackRange;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attack", Meta = (AllowPrivateAccess = true))
	float AttackRadius;

};
