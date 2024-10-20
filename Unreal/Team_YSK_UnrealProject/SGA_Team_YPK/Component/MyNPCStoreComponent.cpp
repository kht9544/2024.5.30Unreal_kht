// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCStoreComponent.h"
#include "MyPlayer.h"
#include "MyInvenComponent.h"
#include "MyItem.h"
#include "MyNPCItem.h"

UMyNPCStoreComponent::UMyNPCStoreComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UMyNPCStoreComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UMyNPCStoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UMyNPCStoreComponent::AddStoreItem(AMyNPCItem* newitem)
{
	if (newitem != nullptr)
	{
		_Npcitems.Add(newitem);
	}
}





