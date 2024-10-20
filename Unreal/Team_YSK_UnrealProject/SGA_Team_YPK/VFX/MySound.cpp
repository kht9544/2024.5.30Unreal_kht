// Fill out your copyright notice in the Description page of Project Settings.


#include "MySound.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

AMySound::AMySound()
{
	PrimaryActorTick.bCanEverTick = false;

	_audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = _audioComponent;
	_audioComponent->bAutoActivate = false;

}

void AMySound::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMySound::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySound::Play(FVector location)
{
	if (_audioComponent && _soundCom)
	{
		SetActorLocation(location);
		_audioComponent->SetSound(_soundCom);
		_audioComponent->Play();
	}
}

bool AMySound::IsPlaying() const
{
	return _audioComponent->IsPlaying();
}

void AMySound::Stop()
{
	if (IsPlaying())
	{
		_audioComponent->Stop();
	}
}

