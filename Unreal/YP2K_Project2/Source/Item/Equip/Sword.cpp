// Fill out your copyright notice in the Description page of Project Settings.

#include "Sword.h"

ASword::ASword()
{
    _equipItemType = EItemType::Sword;
}

void ASword::BeginPlay()
{
    SetItemWithCode(5);
}
