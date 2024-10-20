// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDecalActor.h"
#include "Engine/DecalActor.h"
#include "Components/DecalComponent.h"
#include "MyGameInstance.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"

#include "MyPlayer.h"

AMyDecalActor::AMyDecalActor()
{
    PrimaryActorTick.bCanEverTick = true;
    _delayTime = -1.0f;
    _runTime = 0.0f;
}

void AMyDecalActor::BeginPlay()
{
    Super::BeginPlay();

    _runTime = 0.0f;
    FVector scale = FVector(1.0f, 0.0f, 0.0f);
    _bIsPlay = true;
    _fieldAttackDelegate.AddUObject(this, &AMyDecalActor::DeActiveEvent);
}

void AMyDecalActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (_delayTime == 0.0f || _bIsPlay == false)
        return;

    FVector curScale = GetActorScale();

    if (_runTime > _delayTime && _delayTime > 0.0f)
    {
        _fieldAttackDelegate.Broadcast(GetActorLocation());
        _runTime = 0.0f;
        curScale.Y = 0.0f;
        curScale.Z = 0.0f;

        SetActorScale3D(curScale);
        _bIsPlay = _bLoop;

        return;
    }

    _runTime += DeltaTime;
    curScale.Y = (_runTime / _delayTime) * _areaRadius;
    curScale.Z = (_runTime / _delayTime) * _areaRadius;

    SetActorScale3D(curScale);
}

void AMyDecalActor::Active(FVector location)
{
    _bIsPlay = true;
    SetActorLocation(location);
}

void AMyDecalActor::DeActiveEvent(FVector location)
{
    _bIsPlay = false;
    TArray<AActor *> overlappingActors;
    FVector decalLocation = GetActorLocation();
    float damageRadius = _areaRadius;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPlayer::StaticClass(), overlappingActors);

    for (AActor *actor : overlappingActors)
    {
        if (actor)
        {
            FVector actorLocation = actor->GetActorLocation();
            float distanceToDecal = FVector::Dist(decalLocation, actorLocation);
            if (distanceToDecal <= damageRadius)
            {
                AMyPlayer *player = Cast<AMyPlayer>(actor);
                if (player)
                {
                    float damageAmount = 30.0f;
                    player->TakeDamage(damageAmount, FDamageEvent(), nullptr, this);
                }
            }
        }
    }
}