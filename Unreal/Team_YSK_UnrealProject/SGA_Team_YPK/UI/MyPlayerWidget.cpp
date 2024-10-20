// Fill out your copyright notice in the Description page of Project Settings.



#include "MyPlayerWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UMyPlayerWidget::SetPlHPBar(float ratio)
{
	Pl_HPBar->SetPercent(ratio);
}

void UMyPlayerWidget::SetPlExpBar(float ratio)
{
	Pl_ExpBar->SetPercent(ratio);
}

void UMyPlayerWidget::SetPlLevel(int32 level)
{
	Level->SetText(FText::AsNumber(level));
}
