// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAggroUserWidget.h"
#include "MyPlayer.h"
#include "Components/Widget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h" 


void UMyAggroUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    _playerIndex.Empty(); 
    _damageInfo.Empty(); 

}

void UMyAggroUserWidget::UpdateAggroDisplay(class AMyPlayer* Player, float DamageAmount, float MaxDamage)
{

    if (AggroTarget)
    {
        FString ActorName = Player ? Player->GetName() : TEXT("None");

        ActorName = ActorName.Replace(TEXT("My"), TEXT("")).Replace(TEXT("C"), TEXT("")).Replace(TEXT("BP"), TEXT(""));   
        ActorName = ActorName.Replace(TEXT("__"), TEXT("_"));

        AggroTarget->SetText(FText::FromString(ActorName));
    }

    if (TotalDamage)
    {
        TotalDamage->SetText(FText::AsNumber(DamageAmount));
    }
}



void UMyAggroUserWidget::UpdateAllAggroDisplay(class AMyPlayer* Player, float DamageAmount, float MaxDamage)
{
    TArray<UWidget*> nameBars = PlayerNameInfo->GetAllChildren();  
    TArray<UWidget*> damageBars = DamageInfo->GetAllChildren();   

    if (nameBars.Num() != damageBars.Num())
    {
        return;
    }

    if (int32* index = _playerIndex.Find(Player))
    {
        if (*index >= 0 && *index < nameBars.Num())
        {
            UTextBlock* nameBar = Cast<UTextBlock>(nameBars[*index]);  
            UProgressBar* damageBar = Cast<UProgressBar>(damageBars[*index]); 

            if (nameBar && damageBar)
            {
                FString PlayerName = Player ? Player->GetName() : TEXT("None");

                PlayerName = PlayerName.Replace(TEXT("My"), TEXT(""));
                PlayerName = PlayerName.Replace(TEXT("C"), TEXT(""));
                PlayerName = PlayerName.Replace(TEXT("__"), TEXT("_"));
                PlayerName = PlayerName.Replace(TEXT("BP"), TEXT(""));

                nameBar->SetText(FText::FromString(PlayerName));

                float DamageRatio = FMath::Clamp(DamageAmount / MaxDamage, 0.0f, 1.0f);
                damageBar->SetPercent(DamageRatio);
            }
        }
    }
    else
    {
        int32 newIndex = _playerIndex.Num();
        if (newIndex < nameBars.Num())
        {
            _playerIndex.Add(Player, newIndex);
            _damageInfo.Add(newIndex, Cast<UProgressBar>(damageBars[newIndex])); 

            UTextBlock* nameBar = Cast<UTextBlock>(nameBars[newIndex]);
            UProgressBar* damageBar = Cast<UProgressBar>(damageBars[newIndex]);

            if (nameBar && damageBar)
            {
                FString PlayerName = Player ? Player->GetName() : TEXT("None");
                PlayerName = PlayerName.Replace(TEXT("My"), TEXT(""));
                PlayerName = PlayerName.Replace(TEXT("C"), TEXT(""));
                PlayerName = PlayerName.Replace(TEXT("BP"), TEXT(""));
                nameBar->SetText(FText::FromString(PlayerName));

                float DamageRatio = FMath::Clamp(DamageAmount / MaxDamage, 0.0f, 1.0f);
                damageBar->SetPercent(DamageRatio);
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("더 이상 UI에 플레이어 정보를 추가할 수 없습니다. 최대 플레이어 수를 초과했습니다."));
        }
    }
}