// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "ConsumeItem.generated.h"

UENUM()
enum class ItemSpecipic
{
	HP_Postion,
	MP_Postion,
	EXP_orb,
};

UCLASS()
class PROTOTYPE_API AConsumeItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ItemSpecipic GetSpecipic() { return _specipic; }

protected:
	ItemSpecipic _specipic;
};
