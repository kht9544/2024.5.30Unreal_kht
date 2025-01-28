// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UI/SkillWidget.h"
#include "MyPlayerController.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMyPlayerController();

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext *_inputMappingContext;

	virtual void BeginPlay() override;
};
