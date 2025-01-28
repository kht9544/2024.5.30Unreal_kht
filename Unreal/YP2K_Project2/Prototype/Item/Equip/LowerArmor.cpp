// Fill out your copyright notice in the Description page of Project Settings.

#include "LowerArmor.h"

ALowerArmor::ALowerArmor()
{
    _equipItemType = EItemType::LowerArmor;
}

void ALowerArmor::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(4);
}
