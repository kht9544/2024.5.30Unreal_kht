// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.h"
#include "../Item/Equip/EquipItem.h"
#include "../Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "MyPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquipped, AEquipItem *, EquipItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FINTERECT);

struct FInputActionValue;
class ABaseItem;
class ADragon;


UCLASS()
class PROTOTYPE_API AMyPlayer : public ACreature
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnItemEquipped ItemEquipped;

	bool IsDashing() { return bIsDashing; }
	void OnMonsterHit(class AMonster *HitMonster, const FHitResult &Hit);

	void UpdateCamera(float DeltaTime);

	void SetSkillOnCooldown(int32 index, bool cool) { SkillOnCooldown[index] = cool; }
	void GetItem(ABaseItem *item);

	void Silent();
	void LockAllSkill();
	void UnLockAllSkill();

	virtual void OnAttackEnded(class UAnimMontage *Montage, bool bInterrupted) override;
	void NextCombo();

	void EquipBaseBody();
	void EquipBaseLower();
	void EquipBaseShoulder();

	float GetVertical() { return _vertical; }
	float GetHorizontal() { return _horizontal; }

	FINTERECT interectNPC;

	USkeletalMeshComponent *GetLowerBodyMesh() { return _lowerBodyMesh; }
	USkeletalMeshComponent *GetShoulderBodyMesh() { return _shoulderBodyMesh; }
	USkeletalMeshComponent *GetSwordBodyMesh() { return _swordBodyMesh; }
	USkeletalMeshComponent *GetShieldBodyMesh() { return _shieldBodyMesh; }

	class UInventoryComponent *GetInventory() { return _inventoryComponent; }

private:
	void Move(const FInputActionValue &value);
	void Look(const FInputActionValue &value);
	void JumpA(const FInputActionValue &value);
	void AttackA(const FInputActionValue &value);
	void Skill1(const FInputActionValue &value);
	void Skill2(const FInputActionValue &value);
	void Skill3(const FInputActionValue &value);
	void Skill4(const FInputActionValue &value);
	void Mouse(const FInputActionValue &value);
	void GuardStart(const FInputActionValue &value);
	void GuardEnd(const FInputActionValue &value);
	void LockOn(const FInputActionValue &value);
	void StatUIOpen(const FInputActionValue &value);
	void InvenUIOpen(const FInputActionValue &value);
	void Interect(const FInputActionValue &value);
	void OptionsOpen(const FInputActionValue &value);

	void InitializeDecalPool();

	void UpdateDecalLocation();

	void ConfirmSkillLocation();

	void UpdateTeleportLocation();

	void ConfirmTeleportLocation();

	FVector TargetSkillLocation;

	FRotator SkillRotation;

	bool bIsSkillReadyToCast;
	bool bIsTeleportReadyToCast;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADecalActor> SkillDecalActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ADecalActor> _teleportDecal;

	class ADecalActor *SpawnedDecalActor = nullptr;
	class ADecalActor *SpawnedDecalTeleport = nullptr;

	FTimerHandle TimerHandle_UpdateDecal;
	FTimerHandle TimerHandle_UpdateTeleprotDecal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	TArray<bool> SkillOnCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TMap<EItemType, AEquipItem *> _EquipItems;

	bool bIsLockOn = false;
	bool bIsDashing;
	FVector DashDirection;
	float DashTimeElapsed;
	float DashDuration;
	
	void ResetDashFriction();
	void StartScreenShake();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction *_lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_skill1Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_skill2Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_skill3Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_skill4Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_mouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_StatOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_InvenOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_guardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_LockOnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_OptionsAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *_springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *_camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_Change;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent *_inventoryComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent *_lowerBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent *_shoulderBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent *_swordBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent *_shieldBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMeteorDecal> _decal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
	TArray<AMeteorDecal*> MeteorDecalPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
    int32 MeteorPoolSize = 20;

	AMeteorDecal* GetPooledMeteorDecal();

	UPROPERTY(EditAnywhere, Category = "Dash")
	float _dashDistance;

	UPROPERTY(EditAnywhere, Category = "Dash")
	float _dashSpeed;

	UPROPERTY(EditAnywhere, Category = "Dash")
	FVector2D _moveVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UPlayerAnimInstance *_KnightanimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> _cameraShakeClass;

	FTimerHandle ScreenShakeTimerHandle;
	FTimerHandle MeteorTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (AllowPrivateAccess = "true"))
	class AMonster *_lockOnMonster;

	UPROPERTY(EditAnywhere, Category = "Camera")
	bool _fixedCamera = false;

	UPROPERTY(EditAnywhere, Category = "Skills")
	TSubclassOf<class AFireball> _fireball;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TArray<AFireball*> FireballPool;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
    int32 FireballPoolSize = 20;

	class AFireball* GetPooledFireball();

    float DefaultGroundFriction;
    float DefaultBrakingDecelerationWalking;
};
