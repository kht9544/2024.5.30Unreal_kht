// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHpBar.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyHpBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHpBarvalue(float ratio);

private:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_HPBar;
};
