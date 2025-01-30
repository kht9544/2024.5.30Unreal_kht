 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../Component/StatComponent.h"
#include "Creature.generated.h"

UENUM(BlueprintType)
enum class ESoundType : uint8
{
    HitSound UMETA(DisplayName = "Hit Sound"),
    SwingSound UMETA(DisplayName = "Swing Sound"),
    GuardOn UMETA(DisplayName = "Guard On Sound"),
    GuardOff UMETA(DisplayName = "Guard Off Sound"),
    DeadSound UMETA(DisplayName = "Dead Sound"),
    SkillSound01 UMETA(DisplayName = "Skill Sound 01"),
    SkillSound02 UMETA(DisplayName = "Skill Sound 02"),
    SkillSound03 UMETA(DisplayName = "Skill Sound 03"),
    SkillSound03Shout UMETA(DisplayName = "Skill Sound 03 Shout"),
    SkillSound04Start UMETA(DisplayName = "Skill Sound 04 Start"),
    SkillSound04Durring UMETA(DisplayName = "Skill Sound 04 During"),
    BossMonsterAttack UMETA(DisplayName = "Boss Monster Attack"),
    SkillParticleEffect02 UMETA(DisplayName = "Skill Particle Effect 02"),
    PlayerAttackHitEffect UMETA(DisplayName = "Player Attack Hit Effect"),
    EpicAttackFarSound UMETA(DisplayName = "Epic Attack Far Sound"),
    EpicAttackMagicDotSound UMETA(DisplayName = "Epic Attack Magic Dot Sound"),
    PlayerSkillEffect04Start UMETA(DisplayName = "Player Skill Effect 04 Start"),
    PlayerSkillEffect04Durring UMETA(DisplayName = "Player Skill Effect 04 During"),
    UIBaseSound UMETA(DisplayName = "UI Base Sound"),
    EpicSkeletonEffect UMETA(DisplayName = "Epic Skeleton Effect"),
    EpicSpawnSound UMETA(DisplayName = "Epic Spawn Sound"),
    LevelUpSound UMETA(DisplayName = "Level Up Sound")
};

DECLARE_MULTICAST_DELEGATE(Delegate_AttackEnded);

UCLASS()
class PROTOTYPE_API ACreature : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreature();
	Delegate_AttackEnded _attackEndedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void Disable();
	virtual void AttackHit();

	
	bool GetIsAttacking() { return _isAttacking; }

	UStatComponent *GetStatComponent() { return _StatCom; }

	UFUNCTION()
	virtual void OnAttackEnded(class UAnimMontage *Montage, bool bInterrupted);

	virtual float TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser);

	float GetVertical() { return _vertical; }
	float GetHorizontal() { return _horizontal; }
	UFUNCTION(BlueprintCallable, Category = "UI")
	UUserWidget *GetWidget() const { return _Widget; }
	int32 GetCurHp() { return _StatCom->GetCurHp(); }

	virtual FString GetSoundName(ESoundType SoundType) const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	int32 _curAttackIndex = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _vertical = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float _horizontal = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AttackHit, meta = (AllowPrivateAccess = "true"))
	FVector _hitPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent *_hpWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Guard, meta = (AllowPrivateAccess = "true"))
	bool _isGuarding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = "true"))
	UStatComponent *_StatCom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI, meta = (AllowPrivateAccess = "true"))
	class UUserWidget *_Widget;

};