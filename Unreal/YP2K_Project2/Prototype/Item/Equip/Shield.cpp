// Fill out your copyright notice in the Description page of Project Settings.

#include "Shield.h"

AShield::AShield()
{
    _equipItemType = EItemType::Shield;
}

void AShield::BeginPlay()
{
    SetItemWithCode(6);
}
