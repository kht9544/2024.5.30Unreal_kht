// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerBarWidget.generated.h"

/**
 *
 */
UCLASS()
class PROTOTYPE_API UPlayerBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlHPBar(float ratio);
	void SetPlMPBar(float ratio);
	void SetPlExpBar(float ratio);

	void SetMaxHpBar(int32 MaxHp);
	void SetMaxMpBar(int32 MaxMp);

	UPROPERTY(meta = (BindWidget))
	class UProgressBar *Pl_HPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar *Pl_MPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar *Pl_ExpBar;
};
