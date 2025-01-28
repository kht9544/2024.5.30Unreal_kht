// Fill out your copyright notice in the Description page of Project Settings.

#include "Helmet.h"

AHelmet::AHelmet()
{
    _equipItemType = EItemType::Helmet;
}

void AHelmet::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(1);
}
