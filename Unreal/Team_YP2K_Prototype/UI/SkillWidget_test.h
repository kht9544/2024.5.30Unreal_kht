// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillWidget_test.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API USkillWidget_test : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "Skill")
    void StartCooldown(int32 SkillIndex, float InMaxCooldownTime);

protected:
    virtual void NativeConstruct() override;

    UFUNCTION(BlueprintCallable, Category = "Cooldown")
    void UpdateCooldownText(int32 SkillIndex, float RemainingTime);

	UFUNCTION()
    void UpdateCooldown(int32 SkillIndex);

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Cooltext1;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Cooltext2;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Cooltext3;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* Cooltext4;

    UPROPERTY(meta = (BindWidget))
    class UImage* SkillImage1;

    UPROPERTY(meta = (BindWidget))
    class UImage* SkillImage2;

    UPROPERTY(meta = (BindWidget))
    class UImage* SkillImage3;

    UPROPERTY(meta = (BindWidget))
    class UImage* SkillImage4;

    UPROPERTY(meta = (BindWidget))
    class UImage* Cooldown1;

    UPROPERTY(meta = (BindWidget))
    class UImage* Cooldown2;

    UPROPERTY(meta = (BindWidget))
    class UImage* Cooldown3;

    UPROPERTY(meta = (BindWidget))
    class UImage* Cooldown4;

    TArray<float> CooldownTimes;
    TArray<float> MaxCooldownTimes;
    TArray<FTimerHandle> CooldownTimerHandles;

    TArray<UImage*> SkillImages;
    TArray<UImage*> CooldownOverlays;
    TArray<UTextBlock*> CooldownTexts;
};
