// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyGameInstance.h"
#include "MyHpBar.h"


UMyStatComponent::UMyStatComponent():_invenAttack(0)
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UMyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyStatComponent::Reset()
{
	_curHp = _maxHp;
}

void UMyStatComponent::SetLevelAndInit(int level)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* data = nullptr;	
	if(myGameInstance)
	{
		if(IsBoss == true)
		{
			data = myGameInstance->GetBossStatDataByLevel(level);
			_level = level;
			_maxHp = data->maxHp;
			_attackDamage = data->attackDamage;
			_nextExp = data->nextExp;
			_curExp = 0;
			SetHp(_maxHp);
			IsBoss = false;
		}
		else
		{
			data = myGameInstance->GetStatDataByLevel(level);
			_level = level;
			_maxHp = data->maxHp;
			_attackDamage = data->attackDamage + _invenAttack;
			_nextExp = data->nextExp;
			_curExp = 0;
			SetHp(_maxHp);
			_PILevelDelegate.Broadcast(_level);
		}
			
	
	}	
		
}

void UMyStatComponent::SetNPCLevelAndInit(int level)
{

	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	FMyStatData* Data = nullptr;

	if (myGameInstance)
	{
		Data = myGameInstance->GetNPCStatDataByLevel(level);
		_level = level;
		_maxHp = Data->maxHp;
		_attackDamage = Data->attackDamage;
		_nextExp = Data->nextExp;
		_curExp = 0;
		SetHp(_maxHp);
		_PILevelDelegate.Broadcast(_level);
	}
}

void UMyStatComponent::SetHp(int32 hp)
{
	_curHp = hp;
	if(_curHp <= 0)
	{
		_deathDelegate.Broadcast();
		_deathDelegate.Clear();
		_curHp = 0;
	}
	if(_curHp >_maxHp)
	{
		_curHp = _maxHp;
	}

	float ratio = HpRatio();
	_PlHPDelegate.Broadcast(ratio);

}

int UMyStatComponent::AddCurHp(int32 amount)
{
	int beforeHp = _curHp;

	int afterHp = beforeHp + amount;
	SetHp(afterHp);

	return afterHp - beforeHp;
}

void UMyStatComponent::AddAttackDamage(float amount)
{
	_attackDamage += amount;
	_invenAttack += amount;
}

void UMyStatComponent::AddExp(int32 amount)
{
	if (_level == 3)
		return;
	_curExp += amount;

	while (_curExp >= _nextExp)
    {
        _curExp -= _nextExp;
		_level++;
        SetLevelAndInit(_level);
    }
	float ratio = EXpRatio();
	_PlEXPDelegate.Broadcast(ratio);

}


