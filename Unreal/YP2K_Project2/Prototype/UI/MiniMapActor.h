// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiniMapActor.generated.h"

UCLASS()
class PROTOTYPE_API AMiniMapActor : public AActor
{
    GENERATED_BODY()

public:
    AMiniMapActor();

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UUserWidget> MiniMapWidgetClass;

    UPROPERTY()
    UUserWidget *MiniMapWidget;
};
