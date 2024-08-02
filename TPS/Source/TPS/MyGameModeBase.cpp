// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyCharacter.h"
#include "MyInventoryUI.h"
#include "Components/WidgetComponent.h"
#include "MonsterCharacter.h"

AMyGameModeBase::AMyGameModeBase()
{
	DefaultPawnClass = AMyCharacter::StaticClass();


    _jumpWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("JumpBtn"));
   
    _jumpWidget->SetWidgetSpace(EWidgetSpace::Screen);

    static ConstructorHelpers::FClassFinder<UUserWidget>jumpBtn(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MyJumpButton_BP.MyJumpButton_BP_C'"));
    if (jumpBtn.Succeeded())
    {
        _jumpWidget->SetWidgetClass(jumpBtn.Class);
    }

    ConstructorHelpers::FClassFinder<AMonsterCharacter>monsterCharacter(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster_BP.Monster_BP_C'"));
    if (monsterCharacter.Succeeded())
    {
        DefaultPawnClass = monsterCharacter.Class;
    }

    static ConstructorHelpers::FClassFinder<AMonsterCharacter> myMonster(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Monster_BP.Monster_BP_C'"));

    if (myMonster.Succeeded())
    {
       _monsterClass = myMonster.Class;
    }

    _inventoryWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Inventory"));

    static ConstructorHelpers::FClassFinder<UUserWidget>inventory(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MyInventoryUI_BP.MyInventoryUI_BP_C'"));
    if (inventory.Succeeded())
    {
        _inventoryWidget->SetWidgetClass(inventory.Class);
    }


}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

    if (_inventoryWidget && _inventoryWidget->GetWidgetClass() != nullptr)
    {
        InventoryWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), _inventoryWidget->GetWidgetClass());
        if (InventoryWidgetInstance != nullptr)
        {
            InventoryWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
            InventoryWidgetInstance->AddToViewport();
        }
    }

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.Instigator = GetInstigator();

    // ���� ��ġ�� ȸ��
    FVector SpawnLocation = FVector(430.0f, 1560.0f, 88.0f);
    FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);

    // ���� ����
    AMonsterCharacter* SpawnedActor = GetWorld()->SpawnActor<AMonsterCharacter>(AMonsterCharacter::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

    FVector SpawnLocation1 = FVector(-810.0f,-540.0f, 88.0f);
    FRotator SpawnRotation1 = FRotator(0.0f, 0.0f, 0.0f);

    AMonsterCharacter* SpawnedActor1 = GetWorld()->SpawnActor<AMonsterCharacter>(AMonsterCharacter::StaticClass(), SpawnLocation1, SpawnRotation1, SpawnParams);

    FVector SpawnLocation2 = FVector(170.0f, -610.0f, 88.0f);
    FRotator SpawnRotation2 = FRotator(0.0f, 0.0f, 0.0f);

    AMonsterCharacter* SpawnedActor2 = GetWorld()->SpawnActor<AMonsterCharacter>(AMonsterCharacter::StaticClass(), SpawnLocation2, SpawnRotation2, SpawnParams);

    FVector SpawnLocation3 = FVector(430.0f, 1060.0f, 1188.0f);
    FRotator SpawnRotation3 = FRotator(0.0f, 0.0f, 0.0f);


    AMonsterCharacter* SpawnedActor3 = GetWorld()->SpawnActor<AMonsterCharacter>(AMonsterCharacter::StaticClass(), SpawnLocation3, SpawnRotation3, SpawnParams);

    FVector location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() + FVector(100.0f,100.0f,0.0f);
    FRotator rotator = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();
   
  /* for (int i = 0; i < 3; i++)
   {
      location.X += 100.0 * i;
      AMonsterCharacter* monster = GetWorld()->SpawnActor<AMonsterCharacter>(_monsterClass, location, rotator);
      _monsters.Add(monster);
   }*/
    

    
}
