// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "MySoundManager.generated.h"

class AMySound;

UCLASS()
class SGA_TEAM_YPK_API AMySoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AMySoundManager();

protected:
	virtual void BeginPlay() override;
	void CreateSound(FString name, FString path);
public:	
	virtual void Tick(float DeltaTime) override;

	void PlaySound(FString name, FVector location);
	
private:
	UPROPERTY()
	TMap<FString, TSubclassOf<AMySound>> _soundTable;

	TMap<FString, TArray<AMySound*>> _soundEffectTable;

	UPROPERTY()
	USceneComponent* _rootComponent;

	int32 _poolCount = 5;

	void CreateSoundEffect();

};
