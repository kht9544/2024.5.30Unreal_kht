// Fill out your copyright notice in the Description page of Project Settings.

#include "VFX/ParticleEffect.h"

#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AParticleEffect::AParticleEffect()
{

	PrimaryActorTick.bCanEverTick = false;
	_niagaraCom = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	RootComponent = _niagaraCom;

	_particleCom = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	_particleCom->SetupAttachment(RootComponent);
}

void AParticleEffect::BeginPlay()
{
	Super::BeginPlay();
	_niagaraCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::End);
	End(_niagaraCom);

	_particleCom->OnSystemFinished.AddDynamic(this, &AParticleEffect::EndParticle);
	EndParticle(_particleCom);
}

void AParticleEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AParticleEffect::Play(FVector location, FRotator rotator)
{
	if (_niagaraCom->IsActive() || _particleCom->IsActive())
		return;

	SetActorLocationAndRotation(location, rotator);
	_niagaraCom->ActivateSystem();
	_particleCom->ActivateSystem();
}

bool AParticleEffect::IsPlaying()
{
	if (_niagaraCom->IsActive())
		return true;

	if (_particleCom->IsActive())
		return true;

	return false;
}

void AParticleEffect::PlayOnSkeletalMesh(USkeletalMeshComponent *mesh, FName socketName)
{
	if (!_niagaraCom && !_particleCom)
		return;

	if (_niagaraCom)
	{
		_niagaraCom->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
		_niagaraCom->ActivateSystem();
	}

	if (_particleCom)
	{
		_particleCom->AttachToComponent(mesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, socketName);
		_particleCom->ActivateSystem();
	}
}

void AParticleEffect::End(UNiagaraComponent *niagaraComponent)
{
	if (niagaraComponent)
		niagaraComponent->Deactivate();
}

void AParticleEffect::EndParticle(UParticleSystemComponent *particleComponent)
{
	if (particleComponent)
		particleComponent->DeactivateSystem();
}
