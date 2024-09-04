// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoundManager.h"
#include "MySound.h"
#include "Components/SceneComponent.h"
#include "Engine/World.h"

AMySoundManager::AMySoundManager()
{
	PrimaryActorTick.bCanEverTick = false;
	
	_rootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	_rootComponent->SetupAttachment(RootComponent);

	CreateSound("MyKnight_Swing", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyKnight_AtkSwing_BP.MyKnight_AtkSwing_BP_C'");
	CreateSound("MyKnight_Hit_Sound", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyKnight_AtkHit_BP.MyKnight_AtkHit_BP_C'");
	CreateSound("MyArcher_SwingArrow", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyArcher_AtkSwing_BP.MyArcher_AtkSwing_BP_C'");
	CreateSound("MyArcher_Hit_Sound", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyArcher_AtkHit_BP.MyArcher_AtkHit_BP_C'");
	CreateSound("MyMonster_Atk_Hit", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyBaseMonster_AtkHit_BP.MyBaseMonster_AtkHit_BP_C'");
	CreateSound("MyMonstere_Dead", "/Script/Engine.Blueprint'/Game/Blueprint/Sound/MyMonster_Dead_BP.MyMonster_Dead_BP_C'");
}

void AMySoundManager::BeginPlay()
{
	Super::BeginPlay();
	
	CreateSoundEffect();
}

void AMySoundManager::CreateSound(FString name, FString path)
{
	ConstructorHelpers::FClassFinder<AMySound> soundEffect(*path);
	if (soundEffect.Succeeded())
	{
		_soundTable.Add(name, soundEffect.Class);
	}
}

void AMySoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMySoundManager::CreateSoundEffect()
{
	for (auto classPair : _soundTable)
	{
		FString name = classPair.Key;

		_soundEffectTable.Add(name);
		for (int32 i = 0; i < _poolCount; i++)
		{
			FString tempName = name + FString::FromInt(i);
			FActorSpawnParameters params;
			params.Name = FName(*tempName);
			auto soundEffect = GetWorld()->SpawnActor<AMySound>(classPair.Value, FVector::ZeroVector, FRotator::ZeroRotator, params);

			soundEffect->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			_soundEffectTable[name].Add(soundEffect);
		}
	}

}

void AMySoundManager::PlaySound(FString name, FVector location)
{
	if (_soundEffectTable.Contains(name) == false)
		return;

	auto findSound = _soundEffectTable[name].FindByPredicate(
		[](AMySound* soundEffect)-> bool
		{
			if (soundEffect->IsPlaying())
				return false;
			return true;
		});

	if (findSound)
		(*findSound)->Play(location);

}



