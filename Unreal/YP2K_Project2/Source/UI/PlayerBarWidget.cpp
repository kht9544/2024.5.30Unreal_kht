// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/PlayerBarWidget.h"
#include "Components/ProgressBar.h"

void UPlayerBarWidget::SetPlHPBar(float ratio)
{
	Pl_HPBar->SetPercent(ratio);
}

void UPlayerBarWidget::SetPlMPBar(float ratio)
{
	Pl_MPBar->SetPercent(ratio);
}

void UPlayerBarWidget::SetPlExpBar(float ratio)
{
	Pl_ExpBar->SetPercent(ratio);
}

void UPlayerBarWidget::SetMaxHpBar(int32 MaxHp)
{
	float MinHpScaleX = 1.0f;
	float MaxHpScaleX = 1.8f;

	float NewHPScaleX = FMath::Clamp(float(MaxHp) / 1000.0f, MinHpScaleX, MaxHpScaleX);

	Pl_HPBar->SetRenderScale(FVector2D(NewHPScaleX, 3.0f));
}

void UPlayerBarWidget::SetMaxMpBar(int32 MaxMp)
{
	float MinMPScaleX = 1.0f;
	float MaxMPScaleX = 1.5f;

	float NewMPScaleX = FMath::Clamp(float(MaxMp) / 50.0f, MinMPScaleX, MaxMPScaleX);

	Pl_MPBar->SetRenderScale(FVector2D(NewMPScaleX, 3.0f));
}
