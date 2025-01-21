// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoulderGuard.h"


AShoulderGuard::AShoulderGuard()
{
    _equipItemType = EItemType::ShoulderArmor;
}

void AShoulderGuard::BeginPlay()
{
    Super::BeginPlay();

    SetItemWithCode(2);
}
