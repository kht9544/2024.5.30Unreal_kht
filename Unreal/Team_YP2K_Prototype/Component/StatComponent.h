// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "StatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(DeathDelegate)

DECLARE_MULTICAST_DELEGATE_OneParam(PlHP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PlMP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PIEXP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PILevel, int32);

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

	//FMyStatData()
	//	: level(1)
	//	, MaxHP(100)
	//	, MaxMP(50)
	//	, STR(10)
	//	, DEX(10)
	//	, INT(10)
	//	,BonusPoint(3)
	//	,EXP(100) {}

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
	/*void SetStat();*/
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Reset();

	int32 GetCurHp() { return _curHp; }
	int32 GetMaxHp() { return _maxHp; }
	int32 GetLevel() { return _level; }
	int32 GetExp() { return _curExp; }
	int32 GetCurMp() { return _curMp; }
	int32 GetMaxMp() { return _maxMp; }
	//test
	int32 GetStr()  { return _str; }
	int32 GetDex()  { return _dex; }
	int32 GetInt()  { return _int; }
	int32 GetBonusPoint() { return _bonusPoint; }

	void SetMaxHp(int32 newMaxHp);
	void SetMaxMp(int32 newMaxMp);
	void SetBonusPoint(int32 newBp);
	void SetStr(int32 newstr);
	void SetDex(int32 newdex);
	void SetInt(int32 newint);
	float HpRatio() { return _curHp / (float)_maxHp; }



	void SetHp(int32 hp);
	void SetMp(int32 mp);
	int AddCurHp(int32 amount);
	int AddCurMp(int32 amount);

	void AddAttackDamage(float amount);
	void AddExp(int32 amount);

	void SetLevelInit(int level);
	// cheol 에픽몬스터 
	void SetEpicLevelInit(int level);
	void SetBossLevelInit(int level);

	bool IsDead() { return _curHp <= 0; }

	DeathDelegate _deathDelegate;

	float EXpRatio() { return _curExp / (float)_nextExp; }
	PlHP _PlHPDelegate;
	PlMP _PlMPDelegate;
	PIEXP _PlEXPDelegate;
	PILevel _PILevelDelegate;
	

	//int attckDamage(int32 Attpower, int32 str,int32 dex,int32 _int);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _level;

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
	int32 _attackDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _bonusPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _nextExp;



};
