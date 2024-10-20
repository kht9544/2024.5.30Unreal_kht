// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Consumes/HP_Postion.h"
#include "Base/MyGameInstance.h"

AHP_Postion::AHP_Postion()
{
	
}

void AHP_Postion::BeginPlay()
{
	Super::BeginPlay();

	_specipic = ItemSpecipic::HP_Postion;

	SetItemWithCode(1);
}

void AHP_Postion::UseItem()
{
	Super::UseItem();
}
