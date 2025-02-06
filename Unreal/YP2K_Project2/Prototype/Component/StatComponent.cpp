// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/StatComponent.h"
#include "Base/MyGameInstance.h"
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"
#include "Player/MyPlayer.h"
#include "Player/MyPlayerController.h"
#include "TimerManager.h"
#include "Item/BaseItem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Base/Managers/SoundManager.h"
#include "../Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatComponent::Reset()
{
	SetHp(_maxHp);
	SetMp(_maxMp);
}

void UStatComponent::SetLevelInit(int level)
{
	FMyStatData *Data = nullptr;

	if (GAMEINSTANCE)
	{
		Data = GAMEINSTANCE->GetStatDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_maxMp = Data->MaxMP;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;

		_nextExp = Data->EXP;
		_curExp = 0;
		_attackRadius = 50.0f;
		_attackRange = 300.0f;
		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);
		UpdateUI();
	}
}

void UStatComponent::SetMonsterLevelInit(int level)
{
	FMyStatData *Data = nullptr;

	if (GAMEINSTANCE)
	{
		Data = GAMEINSTANCE->GetMonsterDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_maxMp = Data->MaxMP;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;
		_nextExp = Data->EXP;
		_curExp = 0;

		_attackRadius = 50.0f;
		_attackRange = 300.0f;

		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);
	}
}

void UStatComponent::SetEpicLevelInit(int level)
{
	FMyStatData *Data = nullptr;

	if (GAMEINSTANCE)
	{
		Data = GAMEINSTANCE->GetEpicDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_maxMp = Data->MaxMP;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;

		_nextExp = Data->EXP;
		_curExp = 0;

		_attackRadius = 50.0f;
		_attackRange = 300.0f;

		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);
	}
}

void UStatComponent::SetBossLevelInit(int level)
{
	FMyStatData *Data = nullptr;

	if (GAMEINSTANCE)
	{
		Data = GAMEINSTANCE->GetBossDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_curHp = _maxHp;
		_maxMp = Data->MaxMP;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;

		_nextExp = Data->EXP;

		_attackRadius = 100.0f;
		_attackRange = 500.0f;

		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);
	}
}

void UStatComponent::UpdateUI()
{
	if (Cast<AMyPlayer>(GetOwner()))
	{
		TArray<int32> statPack4UI = { _curHp, _curMp, _str, _dex, _int};
		UIManager->GetInventoryUI()->InitStat(statPack4UI);
	}
}

FString UStatComponent::GetLevelUpName() const
{
	return "P_Status_LevelUp";
}

FString UStatComponent::GetLevelUpSound() const
{
	return "LevelupSound_Cue";
}

void UStatComponent::SetLevel(int32 newLevel)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_level = Data->level;
	_level = FMath::Clamp(newLevel, 0, 100);
}

void UStatComponent::SetMaxHp(int32 newMaxHp)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_maxHp = Data->MaxHP;
	_maxHp = FMath::Clamp(newMaxHp, 0, 10000);
	AddCurHp(newMaxHp);

	_PlMaxHPDelegate.Broadcast(_maxHp);

	UIManager->GetInventoryUI()->UpdateOriginStat((int32)StatType::HP, _maxHp);
	UIManager->GetInventoryUI()->UpdateStat();
}

void UStatComponent::SetMaxMp(int32 newMaxMp)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_maxMp = Data->MaxMP;
	_maxMp = FMath::Clamp(newMaxMp, 0, 10000);
	AddCurMp(newMaxMp);

	_PlMaxMPDelegate.Broadcast(_maxMp);
	UIManager->GetInventoryUI()->UpdateOriginStat((int32)StatType::MP, _maxMp);
	UIManager->GetInventoryUI()->UpdateStat();
}


void UStatComponent::SetBonusPoint(int32 newBp)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_bonusPoint = Data->BonusPoint;
	_bonusPoint = FMath::Clamp(newBp, 0, 10000);
}

void UStatComponent::SetStr(int32 newstr)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_str = Data->STR;
	_str = FMath::Clamp(newstr, 0, 100);

	UIManager->GetInventoryUI()->UpdateOriginStat((int32)StatType::STR, _str);
	UIManager->GetInventoryUI()->UpdateStat();
}


void UStatComponent::SetDex(int32 newdex)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_dex = Data->DEX;
	_dex = FMath::Clamp(newdex, 0, 100);

	UIManager->GetInventoryUI()->UpdateOriginStat((int32)StatType::DEX, _dex);
	UIManager->GetInventoryUI()->UpdateStat();
}

void UStatComponent::SetInt(int32 newint)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_int = Data->INT;
	_int = FMath::Clamp(newint, 0, 100);

	UIManager->GetInventoryUI()->UpdateOriginStat((int32)StatType::INT, _int);
	UIManager->GetInventoryUI()->UpdateStat();
}

void UStatComponent::SetExp(int32 newexp)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData *Data = nullptr;

	_curExp = FMath::Clamp(newexp, 0, 100);
}

void UStatComponent::SetNextExp(int32 newnextexp)
{
	_nextExp = newnextexp;
}


void UStatComponent::SetStatBoost(int32 rate)
{
	float boostFactor = 1.0f + (rate / 100.0f);

	int32 originalStr = _str;
	int32 originalDex = _dex;
	int32 originalInt = _int;

	_str = FMath::Clamp(_str * boostFactor, 0, 100);
	_dex = FMath::Clamp(_dex * boostFactor, 0, 100);
	_int = FMath::Clamp(_int * boostFactor, 0, 100);

	FTimerHandle StatBoostTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(StatBoostTimerHandle, [this, originalStr, originalDex, originalInt]()
										   {
        _str = originalStr;
        _dex = originalDex;
        _int = originalInt; }, 5.0f, false);
}

void UStatComponent::SetHp(int32 hp)
{
	_curHp = hp;
	if (_curHp <= 0)
	{
		_deathDelegate.Broadcast();
		_deathDelegate.Clear();
		_curHp = 0;
	}
	if (_curHp > _maxHp)
	{
		_curHp = _maxHp;
	}

	float ratio = _curHp / (float)_maxHp;
	_PlHPDelegate.Broadcast(ratio);
}

void UStatComponent::SetMp(int32 mp)
{
	_curMp = mp;
	if (_curMp < 0)
	{
		_curMp = 0;
	}

	if (_curMp > _maxMp)
	{
		_curMp = _maxMp;
	}

	float ratio = _curMp / (float)_maxMp;

	_PlMPDelegate.Broadcast(ratio);
}

void UStatComponent::AddMaxHp(int32 amount)
{
	SetMaxHp(_maxHp + amount);
}

void UStatComponent::AddMaxMp(int32 amount)
{
	SetMaxMp(_maxMp + amount);
}


void UStatComponent::AddCurHp(int32 amount)
{
	SetHp(_curHp + amount);
}

void UStatComponent::AddCurMp(int32 amount)
{
	SetMp(_curMp + amount);
}

void UStatComponent::AddStr(int32 amount)
{
	SetStr(_str + amount);
}

void UStatComponent::AddDex(int32 amount)
{
	SetDex(_dex + amount);
}

void UStatComponent::AddInt(int32 amount)
{
	SetInt(_int + amount);
}

void UStatComponent::AddAttackDamage(float amount)
{
	_attackDamage += amount;
}

void UStatComponent::AddExp(int32 amount)
{
	if (_level == 100)
		return;
	_curExp += amount;

	while (_curExp >= _nextExp)
	{
		_curExp -= _nextExp;
		Reset();
		_level++;
		_nextExp = 100 + (_level * 50);
		_PILevelDelegate.Broadcast(_level);

		_bonusPoint += 6;

		UMyGameInstance *GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (GameInstance && GameInstance->GetEffectManager())
		{
			GameInstance->GetEffectManager()->Play(*GetLevelUpName(), GetOwner()->GetActorLocation(), FRotator::ZeroRotator);

			GameInstance->GetSoundManager()->PlaySound(*GetLevelUpSound(), GetOwner()->GetActorLocation());
		}
	}
	float ratio = ExpRatio();
	_PlEXPDelegate.Broadcast(ratio);
}

void UStatComponent::UseItem(class ABaseItem *item)
{
	if(item == nullptr)
		return;
	
	switch (item->GetModStat())
	{
	case StatType::HP:
		AddMaxHp(item->GetValue());
		break;
	case StatType::MP:
		AddMaxMp(item->GetValue());
		break;
	case StatType::CurHP:
		AddCurHp(item->GetValue());
		break;
	case StatType::CurMP:
		AddCurMp(item->GetValue());
		break;
	case StatType::STR:
		AddStr(item->GetValue());
		break;
	case StatType::DEX:
		AddDex(item->GetValue());
		break;
	case StatType::INT:
		AddInt(item->GetValue());
		break;
	default:
		break;
	}
}

void UStatComponent::DropItem(class ABaseItem *item)
{
	if(item == nullptr)
		return;
	
	switch (item->GetModStat())
	{
	case StatType::HP:
		AddMaxHp(-item->GetValue());
		break;
	case StatType::MP:
		AddMaxMp(-item->GetValue());
		break;
	case StatType::CurHP:
		AddCurHp(-item->GetValue());
		break;
	case StatType::CurMP:
		AddCurMp(-item->GetValue());
		break;
	case StatType::STR:
		AddStr(-item->GetValue());
		break;
	case StatType::DEX:
		AddDex(-item->GetValue());
		break;
	case StatType::INT:
		AddInt(-item->GetValue());
		break;
	default:
		break;
	}
}


void UStatComponent::SetDragonLevelInit(int level)
{
	FMyStatData *Data = nullptr;

	if (GAMEINSTANCE)
	{
		Data = GAMEINSTANCE->GetDragonDataByLevel(level);
		_level = level;
		_maxHp = Data->MaxHP;
		_maxMp = Data->MaxMP;
		_str = Data->STR;
		_dex = Data->DEX;
		_int = Data->INT;

		_nextExp = Data->EXP;
		_curExp = 0;
		_attackRadius = 220.0f;
		_attackRange = 1000.0f;
		SetHp(_maxHp);
		SetMp(_maxMp);
		_bonusPoint = Data->BonusPoint;
		_PILevelDelegate.Broadcast(_level);

	}
}