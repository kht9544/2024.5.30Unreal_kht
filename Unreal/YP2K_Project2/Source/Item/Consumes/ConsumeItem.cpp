// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Consumes/ConsumeItem.h"
#include "Components/SphereComponent.h"
#include "Player/MyPlayer.h"

AConsumeItem::AConsumeItem()
{
	_trigger->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}
