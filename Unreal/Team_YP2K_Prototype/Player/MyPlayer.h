// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Creature.h"
#include "../Item/Equip/EquipItem.h"
#include "MyPlayer.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquipped, AEquipItem*, EquipItem);

struct FInputActionValue;
class ABaseItem;

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Climbing UMETA(DisplayName = "Climbing")
};

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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable,Category = "Equipment")
	FOnItemEquipped ItemEquipped;
	
	bool IsDashing() { return bIsDashing; }

	//TODO: Monster로 변경
	void OnMonsterHit(class AMonster *HitMonster, const FHitResult &Hit);


	void SetSkillOnCooldown(int32 index, bool cool) { SkillOnCooldown[index] = cool; }

	UFUNCTION()
	void EquipItem(AEquipItem* equipitem);
	void GetItem(ABaseItem* item);

	void SetEquipItem(EItemType equiptype, AEquipItem* equipitem);

	// Animation
	float GetVertical() { return _vertical; }
	float GetHorizontal() { return _horizontal; }
	
	/*FName GuardStartSectionName;
	FName GuardEndSectionName;
	UPROPERTY(EditAnywhere, Category = "Animation")
	UAnimMontage* GuardMontage;*/
	
	/*UFUNCTION()
	void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);*/

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
	// cheol
	void StatUIOpen(const FInputActionValue &value);
	void InvenUIOpen(const FInputActionValue &value);

	// void CheckForClimbableWall();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skill, meta = (AllowPrivateAccess = "true"))
	TArray<bool> SkillOnCooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment" , meta = (AllowPrivateAccess = "true"))
    TMap<EItemType, AEquipItem*> _EquipItems;

	bool bIsDashing;
	FVector DashDirection;
	float DashTimeElapsed;
	float DashDuration;

	void PerformDash(float DeltaTime);
	void StartScreenShake();
	void CastMeteor();

public:
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
	UInputAction* _InvenOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction *_guardAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent *_springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent *_camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	class USkillWidget_test *_skillWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* _inventoryComponent;

	//  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parkour, meta = (AllowPrivateAccess = "true"))
	//  class UParkourComponent_Test* _parkourComp;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	// class USkeletalMeshComponent* _upperBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* _lowerBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* _shoulderBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* _swordBodyMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* _shieldBodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Decal, meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class AMyDecal> _decal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UStatWidget *_statWidget;

	// MiniMap
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _MiniMapspringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MiniMap, meta = (AllowPrivateAccess = "true"))
	class USceneCaptureComponent2D* _MiniMapCapture;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Minimap, meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* _MinimapSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UMiniMapWidget* _MiniMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float _dashDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float _dashSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	FVector2D _moveVector;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	class UPlayerAnimInstance* _KnightanimInstance;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UCameraShakeBase> _cameraShakeClass;


	FTimerHandle ScreenShakeTimerHandle;
	FTimerHandle MeteorTimerHandle;

	

};
