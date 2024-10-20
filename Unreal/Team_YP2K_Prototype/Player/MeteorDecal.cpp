// Fill out your copyright notice in the Description page of Project Settings.

#include "MeteorDecal.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AMeteorDecal::AMeteorDecal()
{
    PrimaryActorTick.bCanEverTick = true;
    _fallDuration = 3.0f;  // Default fall duration
    _elapsedTime = 0.0f;

    // Initialize Static Mesh for Meteor
    MeteorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeteorMesh"));
    MeteorMesh->SetupAttachment(RootComponent);
}

void AMeteorDecal::BeginPlay()
{
    Super::BeginPlay();
    _elapsedTime = 0.0f;
}

void AMeteorDecal::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Handle Meteor Falling
    if (_elapsedTime < _fallDuration)
    {
       _elapsedTime += DeltaTime;
        UpdateMeteorPosition(DeltaTime);  // 메테오 위치 업데이트

        // Update Decal size as the meteor falls (데칼 크기 업데이트)
        float progress = _elapsedTime / _fallDuration;
        FVector curScale = GetActorScale();
        curScale.Y = progress * _areaRadius;
        curScale.Z = progress * _areaRadius;
        SetActorScale3D(curScale);

        if (_elapsedTime >= _fallDuration)
        {
            OnMeteorImpact();  // 메테오가 바닥에 닿으면 충돌 처리
        }
    }
}

void AMeteorDecal::StartMeteor(FVector startLocation, FVector endLocation, float fallDuration)
{
     _startLocation = startLocation;
    _endLocation = endLocation;
    _fallDuration = fallDuration;
    _elapsedTime = 0.0f;

    MeteorMesh->SetWorldLocation(startLocation);  // 메테오를 하늘에 위치시킴
    SetActorLocation(endLocation);  // 데칼은 바닥에 위치
    _bIsPlay = true;
}

void AMeteorDecal::OnMeteorImpact()
{
   _fieldAttackDelegate.Broadcast(GetActorLocation());

    // 메테오 메시 숨김
    MeteorMesh->SetVisibility(false);

    // 데칼 폭발 처리
    DeActiveEvent(GetActorLocation());
}

void AMeteorDecal::UpdateMeteorPosition(float DeltaTime)
{
     FVector currentLocation = FMath::Lerp(_startLocation, _endLocation, _elapsedTime / _fallDuration);
    MeteorMesh->SetWorldLocation(currentLocation); 
}