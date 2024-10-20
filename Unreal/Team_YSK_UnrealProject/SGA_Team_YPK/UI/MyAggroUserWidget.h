// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyAggroUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SGA_TEAM_YPK_API UMyAggroUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;


public:
	UFUNCTION(BlueprintCallable, Category = "Aggro")
	void UpdateAggroDisplay(class AMyPlayer* Player, float DamageAmount, float MaxDamage);

	UFUNCTION(BlueprintCallable, Category = "Aggro")
	void UpdateAllAggroDisplay(class AMyPlayer* Player, float DamageAmount, float MaxDamage);
    
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* AggroTarget;

    UPROPERTY(meta = (BindWidget))
    class UTextBlock* TotalDamage;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerNameInfo;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* DamageInfo;

	UPROPERTY()
	TMap<class AMyPlayer*, int32> _playerIndex;

	UPROPERTY()
	TMap<int32, class UProgressBar*> _damageInfo;


	
};
