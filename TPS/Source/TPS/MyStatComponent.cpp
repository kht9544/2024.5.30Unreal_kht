// Fill out your copyright notice in the Description page of Project Settings.


#include "MyStatComponent.h"
#include "MyCharacter.h"
#include "MyHpBar.h"
#include "MyGameInstance.h"

// Sets default values for this component's properties
UMyStatComponent::UMyStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UMyStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// ...
}

void UMyStatComponent::Reset()
{
	_curHp = _maxHp;
}

void UMyStatComponent::SetLevelAndInit(int level)
{
	auto myGameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	if (myGameInstance)
	{
		FMyStatData* data = myGameInstance->GetStatDataByLevel(level);
		_maxHp = data->maxHp;
		_attackDamage = data->attack;
		_curHp = _maxHp;

		UE_LOG(LogTemp, Log, TEXT(" hp : % d, attakc : % d"), _maxHp, _attackDamage);
	}
}

void UMyStatComponent::SetHp(int32 hp)
{
	//_curHp의 수정은 무조건 이 함수를 통해서 이루워진다
	// 이 함수가 호출될떄 마다 hpbar가 바뀌면 된다

	_curHp = hp;
	if (_curHp < 0)
		_curHp = 0;

	if (_curHp > _maxHp)
		_curHp = _maxHp;

	float ratio = HpRatio();
	_hpChangedDelegate.Broadcast(ratio);

}

int UMyStatComponent::AddCurHp(float amount)
{
	int beforeHp = _curHp;
	//amount damage가 들어왔을떄
	//방어력 ,데미지 경감등의 옵션으로 amount가줄어든채로 curHp에 더함
	int afterHp = beforeHp + amount;
	SetHp(afterHp);

	return afterHp - beforeHp;
}

void UMyStatComponent::AddAttackDamage(float amount)
{
	_attackDamage += amount;

}