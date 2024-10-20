#include "SkillWidget_test.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Player/MyPlayer.h"
#include "TimerManager.h"

void USkillWidget_test::NativeConstruct()
{    
    SkillImages.Add(SkillImage1);
    SkillImages.Add(SkillImage2);
    SkillImages.Add(SkillImage3);
    SkillImages.Add(SkillImage4);

    CooldownOverlays.Add(Cooldown1);
    CooldownOverlays.Add(Cooldown2);
    CooldownOverlays.Add(Cooldown3);
    CooldownOverlays.Add(Cooldown4);

    CooldownTexts.Add(Cooltext1);
    CooldownTexts.Add(Cooltext2);
    CooldownTexts.Add(Cooltext3);
    CooldownTexts.Add(Cooltext4);

    CooldownTimes.Init(0.0f, 4);
    MaxCooldownTimes.Init(0.0f, 4);
    CooldownTimerHandles.Init(FTimerHandle(), 4);

    for(UImage* cd : CooldownOverlays)
    {
        if(cd)
        {
            cd->SetOpacity(0.0f);
        }
    }
}

void USkillWidget_test::UpdateCooldownText(int32 SkillIndex, float RemainingTime)
{
    if (CooldownTexts[SkillIndex])
    {
        if (RemainingTime <= 0.0f)
        {
            CooldownTexts[SkillIndex]->SetText(FText::FromString(TEXT("")));
        }
        else
        {
            FString CooldownText = FString::Printf(TEXT("%.1f"), RemainingTime);
            CooldownTexts[SkillIndex]->SetText(FText::FromString(CooldownText));
        }
    }
}

void USkillWidget_test::StartCooldown(int32 SkillIndex, float InMaxCooldownTime)
{
    if (SkillIndex < 0 || SkillIndex >= CooldownOverlays.Num()) return;

    MaxCooldownTimes[SkillIndex] = InMaxCooldownTime;
    CooldownTimes[SkillIndex] = MaxCooldownTimes[SkillIndex];

    if (CooldownOverlays[SkillIndex])
    {
        CooldownOverlays[SkillIndex]->SetOpacity(0.5f);
    }

    GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandles[SkillIndex], [this, SkillIndex]()
    {
        float DeltaTime = GetWorld()->GetDeltaSeconds();
        CooldownTimes[SkillIndex] -= DeltaTime;

        UpdateCooldown(SkillIndex);

        if (CooldownTimes[SkillIndex] <= 0.0f)
        {
            CooldownTimes[SkillIndex] = 0.0f;
            GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandles[SkillIndex]);

            if (CooldownOverlays[SkillIndex])
            {
                CooldownOverlays[SkillIndex]->SetOpacity(0.0f);
            }

            AMyPlayer* Player = Cast<AMyPlayer>(GetWorld()->GetFirstPlayerController()->GetPawn());
            if (Player)
            {
                Player->SetSkillOnCooldown(SkillIndex,false);
            }
        }
    }, 0.1f, true);
}


void USkillWidget_test::UpdateCooldown(int32 SkillIndex)
{
    if (SkillIndex < 0 || SkillIndex >= CooldownTimes.Num()) return;

    CooldownTimes[SkillIndex] -= GetWorld()->DeltaTimeSeconds;

    if (CooldownTimes[SkillIndex] <= 0.0f)
    {
        GetWorld()->GetTimerManager().ClearTimer(CooldownTimerHandles[SkillIndex]);

        if (CooldownOverlays[SkillIndex])
        {
            FSlateBrush Brush = CooldownOverlays[SkillIndex]->Brush;
            Brush.ImageSize = FVector2D(Brush.ImageSize.X, SkillImage1->GetDesiredSize().Y);
            CooldownOverlays[SkillIndex]->SetBrush(Brush);

            CooldownOverlays[SkillIndex]->SetOpacity(0.0f);
        }
    }
    else
    {
        float Percent = CooldownTimes[SkillIndex] / MaxCooldownTimes[SkillIndex];

        if (CooldownOverlays[SkillIndex])
        {
            FSlateBrush Brush = CooldownOverlays[SkillIndex]->Brush;
            Brush.ImageSize = FVector2D(Brush.ImageSize.X, SkillImage1->GetDesiredSize().Y * Percent);
            CooldownOverlays[SkillIndex]->SetBrush(Brush);

            CooldownOverlays[SkillIndex]->SetOpacity(0.5f); 
        }
    }

    UpdateCooldownText(SkillIndex, CooldownTimes[SkillIndex]);
}
