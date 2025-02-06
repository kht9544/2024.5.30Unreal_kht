// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(DeathDelegate)

DECLARE_MULTICAST_DELEGATE_OneParam(PlHP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PlMP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PlMaxHP, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(PlMaxMP, int32);
DECLARE_MULTICAST_DELEGATE_OneParam(PIEXP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PILevel, int32);

UENUM()
enum class StatType
{
	HP,
	MP,
	STR,
	DEX,
	INT,
	CurHP,
	CurMP,
	Other
};

USTRUCT()
struct FMyStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 STR;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 INT;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BonusPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EXP;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void Reset();
	void SetUI();

	int32 GetCurHp() { return _curHp; }
	int32 GetMaxHp() { return _maxHp; }
	float HpRatio() { return _curHp / (float)_maxHp; }
	int32 GetLevel() { return _level; }
	int32 GetExp() { return _curExp; }
	float ExpRatio() { return _curExp / (float)_nextExp; }
	int32 GetCurMp() { return _curMp; }
	int32 GetMaxMp() { return _maxMp; }
	int32 GetNextExp() { return _nextExp; }
	int32 GetStr() { return _str; }
	int32 GetDex() { return _dex; }
	int32 GetInt() { return _int; }
	float GetAttackRange() { return _attackRange; }
	float GetAttackRadius() { return _attackRadius; }
	int32 GetBonusPoint() { return _bonusPoint; }

	void SetLevel(int32 newLevel);
	void SetMaxHp(int32 newMaxHp);
	void SetMaxMp(int32 newMaxMp);
	void SetHp(int32 hp);
	void SetMp(int32 mp);
	void SetBonusPoint(int32 newBp);
	void SetStr(int32 newstr);
	void SetDex(int32 newdex);
	void SetInt(int32 newint);
	void SetExp(int32 newexp);
	void SetNextExp(int32 newnextexp);
	void SetStatBoost(int32 rate);
	void SetStun(bool stun) { _stunned = stun; }
	void SetAttackRange(int32 newrange) { _attackRange = newrange; }
	void SetAttackRadius(int32 newradius) { _attackRadius = newradius; }
	void SetAttackDamage(int32 newdamage) { _attackDamage = newdamage; }

	void AddMaxHp(int32 amount);
	void AddMaxMp(int32 amount);
	void AddCurHp(int32 amount);
	void AddCurMp(int32 amount);
	void AddStr(int32 amount);
	void AddDex(int32 amount);
	void AddInt(int32 amount);
	void AddAttackDamage(float amount);
	void AddExp(int32 amount);

	void UseItem(class ABaseItem *item);
	void DropItem(class ABaseItem *item);



	void SetLevelInit(int level);
	void SetMonsterLevelInit(int level);
	void SetEpicLevelInit(int level);
	void SetBossLevelInit(int level);

	void SetDragonLevelInit(int level);
	void UpdateUI();

	bool IsDead() { return _curHp <= 0; }


	PlHP _PlHPDelegate;
	PlMaxHP _PlMaxHPDelegate;
	PlMP _PlMPDelegate;
	PlMaxMP _PlMaxMPDelegate;
	PIEXP _PlEXPDelegate;
	PILevel _PILevelDelegate;
	DeathDelegate _deathDelegate;

	virtual FString GetLevelUpName() const;
	virtual FString GetLevelUpSound() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _level;

	TArray<TMap<FString, int32>> _stats;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _maxHp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _maxMp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _str;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _dex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _int;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	float _attackRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	float _attackRadius;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _attackDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _bonusPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _nextExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	bool _stunned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	float _stunDuration;

	float _stunTimer;
};
