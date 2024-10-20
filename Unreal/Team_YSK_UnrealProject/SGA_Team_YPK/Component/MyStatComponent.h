// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "MyStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(DeathDelegate)

DECLARE_MULTICAST_DELEGATE_OneParam(PlHP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PIEXP, float);
DECLARE_MULTICAST_DELEGATE_OneParam(PILevel, int32);

USTRUCT()
struct FMyStatData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 maxHp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 attackDamage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 nextExp;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAM_YPK_API UMyStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyStatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Reset();

	int32 GetCurHp(){return _curHp;}
	int32 GetLevel(){return _level;}
	int32 GetExp(){return _curExp;}
	int32 GetAttackDamage() {return _attackDamage;}
	float HpRatio(){return _curHp/(float)_maxHp;}

	void SetLevelAndInit(int level);

	void SetNPCLevelAndInit(int level);

	void SetHp(int32 hp);
	void SetBoss(bool boss){IsBoss = boss;}
	int AddCurHp(int32 amount);
	void AddAttackDamage(float amount);
	void AddExp(int32 amount);


	bool IsDead() {return _curHp <= 0; }

	DeathDelegate _deathDelegate;

	float EXpRatio() { return _curExp / (float)_nextExp; }
	PlHP _PlHPDelegate;
	PIEXP _PlEXPDelegate;
	PILevel _PILevelDelegate;


protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _level;		

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curHp;		

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _maxHp;		

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _attackDamage;		

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _curExp;		

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _nextExp;	

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	bool IsBoss = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Stat, meta = (AllowPrivateAccess = true))
	int32 _invenAttack;
};
