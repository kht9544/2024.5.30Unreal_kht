// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEffect.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"


// Sets default values
AMyEffect::AMyEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	RootComponent = _particleCom;

	_particleSceneCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleScene"));
	_particleSceneCom->SetupAttachment(RootComponent);
		
}

// Called when the game starts or when spawned
void AMyEffect::BeginPlay()
{
	Super::BeginPlay();
	
	_particleCom->OnSystemFinished.AddDynamic(this, &AMyEffect::End);
	End(_particleCom);

	_particleSceneCom->OnSystemFinished.AddDynamic(this, &AMyEffect::End);
	End(_particleSceneCom);
}

// Called every frame
void AMyEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyEffect::Play(FVector location, FRotator rotator)
{
	if (_particleCom->IsActive() || _particleSceneCom->IsActive())
		return;


	SetActorLocationAndRotation(location, rotator);
	_particleCom->ActivateSystem();
	_particleSceneCom->ActivateSystem();
}


bool AMyEffect::IsPlaying()
{
	if (_particleCom->IsActive())
		return true;

	if (_particleSceneCom->IsActive())
		return true;

	return false;
}


void AMyEffect::End(UParticleSystemComponent* particle)
{
	if (particle)
		particle->DeactivateSystem();
}

void AMyEffect::EndSystem(UParticleSystem* particle)
{
	if (particle && _particleSceneCom)
	{
		_particleSceneCom->SetTemplate(particle);
		_particleSceneCom->ActivateSystem();
	}

}


