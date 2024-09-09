// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC.h"
#include "MyNPCStoreUI.h"
#include "Components/WidgetComponent.h"
#include "MyNPCStoreUI.h"
#include "MyNPCStoreComponent.h"

AMyNPC::AMyNPC()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> np
	(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/SK_SKnight_07_full.SK_SKnight_07_full'"));

	if (np.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(np.Object);

	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UMyNPCStoreUI> store
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/NPCStoreUI_BP.NPCStoreUI_BP_C'"));

	if (store.Succeeded())
	{
		_storeWidget = CreateWidget<UMyNPCStoreUI>(GetWorld(), store.Class);
	}
}

void AMyNPC::BeginPlay()
{
	Super::BeginPlay();

	if (_storeWidget)
	{
		_storeWidget->AddToViewport();
		_storeWidget->SetVisibility(ESlateVisibility::Hidden);
	}
   
   
}

void AMyNPC::NPCStoreUI(bool UImark)
{

	if (_storeWidget)
	{
		if (UImark)
		{
			_storeWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			_storeWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}
