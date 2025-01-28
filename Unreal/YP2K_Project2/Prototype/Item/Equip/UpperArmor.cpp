// Fill out your copyright notice in the Description page of Project Settings.

#include "UpperArmor.h"

AUpperArmor::AUpperArmor()
{
    _equipItemType = EItemType::UpperArmor;
}

void AUpperArmor::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(3);
}
