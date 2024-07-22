// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UE_KHT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* _sm;

	UPROPERTY(EditAnywhere, Category = "Trans")
	float _rotationSpeed = 2.0f;

	UPROPERTY(EditAnywhere, Category = "Trans")
	float _moveSpeed = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target")
	AMyActor* TargetActor;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 1.0f; // 회전 속도를 조절할 변수

};
