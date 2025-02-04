#pragma once

#include "CoreMinimal.h"
#include "MyCreature.h"
#include "InputActionValue.h"
#include "MyPlayer.generated.h"

class UMyStatComponent;

UCLASS()
class SGA_TEAM_YPK_API AMyPlayer : public AMyCreature
{
	GENERATED_BODY()

public:
	AMyPlayer();
	virtual void Tick(float DeltaTime) override;
	virtual void Disable() override;

public:
	void AddAttackDamage(AActor* actor, int amount);
	void AddItemToCharacter(class AMyNPCItem* item);
	void DropItemFromCharacter();

	virtual void Attack_AI(){}

	class UMyInvenUI* GetInvenWidget() {return _invenWidget;}

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void AttackHit() override;

	virtual void Move(const FInputActionValue& value);
	virtual void Look(const FInputActionValue& value);
	virtual void JumpA(const FInputActionValue& value);
	
	virtual void Inven(const  FInputActionValue& value);
	virtual void Mouse(const FInputActionValue& value);
	virtual void Interaction(const FInputActionValue& value);
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack(const FInputActionValue& value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* _lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _InventoryAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _itemDropAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _mouseAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* _interactionAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UMyAnimInstance* _animInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC, meta = (AllowPrivateAccess = "true"))
	float InteractionDistance = 200.0f;

	class AMyNPC* StoreNPC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	class AMyMonster* _lastAttackedMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = "true"))
	class UMyInvenUI* _invenWidget;
};
