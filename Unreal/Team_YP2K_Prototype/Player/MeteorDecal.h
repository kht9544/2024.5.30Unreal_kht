// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/MyDecal.h"
#include "MeteorDecal.generated.h"

UCLASS()
class PROTOTYPE_API AMeteorDecal : public AMyDecal
{
    GENERATED_BODY()

public:
    AMeteorDecal();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void StartMeteor(FVector startLocation, FVector endLocation, float fallDuration);

protected:
    FVector _startLocation;
    FVector _endLocation;
    float _fallDuration;
    float _elapsedTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meteor")
    UStaticMeshComponent* MeteorMesh;

    UFUNCTION()
    void OnMeteorImpact();

	void UpdateMeteorPosition(float DeltaTime);


	// TODO: 이펙트
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meteor", meta = (AllowPrivateAccess = "true"))
	// class UParticleSystem* _explosionEffect;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meteor", meta = (AllowPrivateAccess = "true"))
	// class USoundBase* _explosionSound;
};
	

