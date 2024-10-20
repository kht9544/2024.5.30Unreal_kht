// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyStatComponent.h"
#include "GameFramework/Character.h"
#include "MyCreature.generated.h"

DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);

UCLASS()
class SGA_TEAM_YPK_API AMyCreature : public ACharacter

{
	GENERATED_BODY()

public:
	AMyCreature();
	Delegate_AttackEnded _attackEndedDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Init();
	virtual void Disable();

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual FString GetHitParticleName() const;

	virtual FString GetHitSoundName() const;
	virtual FString GetSwingSoundName() const;
	virtual FString GetDeadSoundName() const;

	virtual void Attackhit();
	int32 GetCurHp() { return _statCom->GetCurHp(); }

	UFUNCTION()
	void OnAttackEnded(class UAnimMontage* Montage, bool bInterrupted);
	
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	float GetVertical() {return _vertical;}
	float GetHorizontal() {return _horizontal;}

	virtual void ShowHP();
	virtual void HideHP();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttcking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 _curAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	class AMyMonster* _lastAttackedMonster;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _hpWidget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyStatComponent* _statCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inven, meta = (AllowPrivateAccess = "true"))
	class UMyInvenComponent* _invenCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* _Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UUserWidget* _screenWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;
	



};
