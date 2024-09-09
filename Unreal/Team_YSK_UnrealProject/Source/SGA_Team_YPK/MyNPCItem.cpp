// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCItem.h"
#include "MyItem.h"
#include "MyPlayer.h"
#include "Engine/DataTable.h"


AMyNPCItem::AMyNPCItem()
{
    PrimaryActorTick.bCanEverTick = false;


    RootComponent = _meshComponent;

    static ConstructorHelpers::FObjectFinder<UDataTable> DataTable
    (TEXT("/Script/Engine.DataTable'/Game/Data/ItemDataTable.ItemDataTable'"));

    if (DataTable.Succeeded())
    {
        ItemDataTable = DataTable.Object;
        ItemRowHandle.DataTable = ItemDataTable;
      


        if (ItemDataTable)
        {
            TArray<FName> RowNames = ItemDataTable->GetRowNames();
            for (const FName& RowName : RowNames)
            {
                FItemData* Row = ItemDataTable->FindRow<FItemData>(RowName, TEXT("LookupItemData"));
                if (Row)
                {
                    _ItemData.Add(*Row);  
                }
            }
        }
    }
   
}


void AMyNPCItem::OnConstruction(const FTransform& Transform)
{
    ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
    if (ItemRow != nullptr)
    {
        _meshComponent->SetSkeletalMesh((*ItemRow).ItemMesh);
        _meshComponent->SetSimulatePhysics(false);
    }

}


UTexture2D* AMyNPCItem::GetItemTexture() const
{
    if (ItemRow)
    {
        return ItemRow->ItemTexture;
    }
    return nullptr;
}

void AMyNPCItem::InitializeItem(int32 ItemId)
{
    _itemId = ItemId;

    if (ItemDataTable)
    {
        FName RowName = FName(*FString::FromInt(_itemId));
        FItemData* ItemData = ItemDataTable->FindRow<FItemData>(RowName, "");

        if (ItemData)
        {
            _meshComponent->SetSkeletalMesh(ItemData->ItemMesh);
            _meshComponent->SetSimulatePhysics(false);
        }
    }
}

void AMyNPCItem::BeginPlay()
{
	Super::BeginPlay();

    if (ItemDataTable && ItemRowHandle.RowName != NAME_None)
    {
        ItemRow = ItemDataTable->FindRow<FItemData>(ItemRowHandle.RowName, "");
        if (_itemId != -1)
        {
            InitializeItem(_itemId);
        }
    }
}

void AMyNPCItem::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
    Super::OnMyCharacterOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromWeep, SweepResult);
    auto myPlayer = Cast<AMyPlayer>(OtherActor);
    if (myPlayer)
    {
        myPlayer->AddAttackDamage(this, 50);
        myPlayer->AddItemToCharacter(this);
        Disable();
    }
}

