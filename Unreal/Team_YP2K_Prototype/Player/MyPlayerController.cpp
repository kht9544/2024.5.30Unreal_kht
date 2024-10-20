// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "../UI/SkillWidget_test.h"


AMyPlayerController::AMyPlayerController()
{

}

void AMyPlayerController::BeginPlay()
{

    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem *subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (subSystem)
    {
        subSystem->AddMappingContext(_inputMappingContext, 0);
    }


    if (SkillWidgetClass)
    {
        SkillWidgetInstance = CreateWidget<USkillWidget_test>(this, SkillWidgetClass);
        if (SkillWidgetInstance)
        {
            SkillWidgetInstance->AddToViewport();
        }
    }



}


