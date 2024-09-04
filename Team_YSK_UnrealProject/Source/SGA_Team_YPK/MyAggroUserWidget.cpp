// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAggroUserWidget.h"
#include "MyPlayer.h"
#include "Components/Widget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void UMyAggroUserWidget::UpdateAggroDisplay(class AMyPlayer *Player, float DamageAmount)
{
    if (AggroTarget)
    {
        FString ActorName = Player ? Player->GetName() : TEXT("None");
        AggroTarget->SetText(FText::FromString(ActorName));
    }

    if (TotalDamage)
    {
        TotalDamage->SetText(FText::AsNumber(DamageAmount));
    }

   

}

void UMyAggroUserWidget::UpdateAllAggroDisplay(class AMyPlayer* Player, float DamageAmount)
{
    TArray<UWidget*> nameBars = PlayerNameInfo->GetAllChildren();
    TArray<UWidget*> damageBars = DamageInfo->GetAllChildren();

    if (nameBars.Num() != damageBars.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerNameInfo와 DamageInfo의 텍스트 블록 수가 일치하지 않습니다."));
        return;
    }

    if (int32* index = _playerIndex.Find(Player))
    {
        if (*index >= 0 && *index < nameBars.Num())
        {
            UTextBlock* nameBar = Cast<UTextBlock>(nameBars[*index]);
            UTextBlock* damageBar = Cast<UTextBlock>(damageBars[*index]);

            if (nameBar)
            {
                FString PlayerName = Player ? Player->GetName() : TEXT("None");
                nameBar->SetText(FText::FromString(PlayerName));
            }

            if (damageBar)
            {
                damageBar->SetText(FText::AsNumber(DamageAmount));
            }
        }
    }
    else
    {
        int32 newIndex = _playerIndex.Num();
        if (newIndex < nameBars.Num())
        {
            _playerIndex.Add(Player, newIndex);
            _damageInfo.Add(newIndex, Cast<UTextBlock>(damageBars[newIndex]));

            UTextBlock* nameBar = Cast<UTextBlock>(nameBars[newIndex]);
            UTextBlock* damageBar = Cast<UTextBlock>(damageBars[newIndex]);

            if (nameBar)
            {
                FString PlayerName = Player ? Player->GetName() : TEXT("None");
                nameBar->SetText(FText::FromString(PlayerName));
            }

            if (damageBar)
            {
                damageBar->SetText(FText::AsNumber(DamageAmount));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("UI에 더 이상 플레이어 정보를 추가할 수 없습니다."));
        }
    }
}

