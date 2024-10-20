// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseItem.h" 
#include "EquipItem.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
    UpperArmor,
    LowerArmor,
    ShoulderArmor,
    Sword,
    Shield
};

UCLASS()
class PROTOTYPE_API AEquipItem : public ABaseItem 
{
    GENERATED_BODY()
    
public:    
    // Sets default values for this actor's properties
    AEquipItem();

    ItemType GetArmorType(){return _Type;}
    EItemType GetEquipType(){return _equipItemType;}

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
  
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    virtual void EquipPlayer(class AMyPlayer* Player);

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Socket")
    FName AttachSocketName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipItem")
    EItemType _equipItemType;

public:  
    UFUNCTION()
    virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EquipItem")
    class USkeletalMesh* _equipItem;
};
