// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MiniMapWidget.h"
#include "Player/MyPlayer.h"
#include "Components/Image.h"

void UMiniMapWidget::NativeConstruct()
{
    //	MapImage = LoadObject<UImage>(nullptr, TEXT("/Script/Engine.Material'/Game/Blueprint/UI/Map/MapTesm.MapTesm'"));
    //UMaterialInterface* MapMaterial = LoadObject<UMaterialInterface>(nullptr,
    //    TEXT("/Script/Engine.Material'/Game/Blueprint/UI/Map/MapTesm.MapTesm'"));
    //// 현재 기본 맵 
    //// /Script/Engine.Material'/Game/Blueprint/UI/Map/MapTesm.MapTesm' 테스트맵
    //if (MapMaterial)
    //{
    //    if (MapImage)
    //    {
    //        MapImage->SetBrushFromMaterial(MapMaterial);
    //    }
    //}

}
