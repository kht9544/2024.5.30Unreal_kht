// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	_sm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = _sm;


	static ConstructorHelpers::FObjectFinder<UStaticMesh> mesh = TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Props/SM_Chair.SM_Chair'");

	if (mesh.Succeeded())
	{
		_sm->SetStaticMesh(mesh.Object);
	}

	UE_LOG(LogTemp, Warning, TEXT("Constructor"));
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Error, TEXT("Begin Play"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Log , TEXT("Tick : %f"),DeltaTime);

	/*FRotator rot = FRotator(0.0f, 1.0f, 0.0f);
	AddActorLocalRotation(rot * _rotationSpeed * DeltaTime);*/

	//FVector tempV = GetActorLocation();
	//UE_LOG(LogTemp, Log, TEXT("%f,%f,%f"), tempV.X, tempV.Y, tempV.Z);

	FVector moveV = GetActorLocation(); 
	FVector NewLocation = moveV + FVector(0.0f, 1.0f, 0.0f); 
	SetActorLocation(NewLocation);


	if (TargetActor)
	{
		// Get the location of the target actor
		FVector TargetLocation = TargetActor->GetActorLocation();
		// Get the location of this actor
		FVector CurrentLocation = GetActorLocation();
		// Calculate the direction vector from this actor to the target actor
		FVector DirectionToTarget = TargetLocation - CurrentLocation;
		// Create a rotation that faces the target
		FRotator TargetRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);

		// Get the current rotation
		FRotator CurrentRotation = GetActorRotation();
		// Interpolate between current rotation and target rotation
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);

		// Set this actor's rotation
		SetActorRotation(NewRotation);
	}
	

}

