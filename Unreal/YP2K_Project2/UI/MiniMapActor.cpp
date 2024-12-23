// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniMapActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "Player/MyPlayer.h"
#include "Blueprint/UserWidget.h"


#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "UI/MiniMapWidget.h"


AMiniMapActor::AMiniMapActor()
{
    PrimaryActorTick.bCanEverTick = true;
    static ConstructorHelpers::FClassFinder<UUserWidget> MiniMap
    (TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/Map/TEstMap.TEstMap_C'"));
    // 
    if (MiniMap.Succeeded())
    {
        MiniMapWidgetClass = MiniMap.Class;
    }

}

void AMiniMapActor::BeginPlay()
{
    Super::BeginPlay();

    if (MiniMapWidgetClass)
    {
        MiniMapWidget = CreateWidget< UMiniMapWidget>(GetWorld(), MiniMapWidgetClass);
        if (MiniMapWidget)
        {
            MiniMapWidget->AddToViewport();
        }
    }


}

void AMiniMapActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AMyPlayer* PlCh = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (PlCh)
    {
        FVector PlLocation = PlCh->GetActorLocation();
        FRotator PlRotation = PlCh->GetActorRotation();

        UMaterialParameterCollection* MapCollection = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Script/Engine.MaterialParameterCollection'/Game/Blueprint/UI/Map/MapCon.MapCon'"));
        if (MapCollection)
        {
            UMaterialParameterCollectionInstance* CollectionInstance = GetWorld()->GetParameterCollectionInstance(MapCollection);
            if (CollectionInstance)
            {
                CollectionInstance->SetVectorParameterValue(FName("PlayerLaction"), PlLocation);
                float PlYaw = PlRotation.Yaw;

                float AdjustedYaw = (PlYaw < 0) ? PlYaw + 360.0f : PlYaw;

                float testYaw = AdjustedYaw / 360;

                CollectionInstance->SetScalarParameterValue(FName("PlayerYaw"), testYaw);
            }
        }
    }
}