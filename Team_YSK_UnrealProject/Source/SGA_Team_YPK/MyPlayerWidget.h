// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerWidget.generated.h"


UCLASS()
class SGA_TEAM_YPK_API UMyPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPlHPBar(float ratio);
	void SetPlExpBar(float ratio);
	void SetPlLevel(int32 level);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Pl_HPBar;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Pl_ExpBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Level;

	
};
