// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMonster.h"
#include "MyItem.h"
#include "MyCreature.h"
#include "MyPlayer.h"
#include "MyInvenComponent.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyHpBar.h"

AMyMonster::AMyMonster()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ms
	(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_01/mesh/SK_SKnigh_01_full.SK_SKnigh_01_full'"));
	if (ms.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ms.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<AMyItem> MI
	(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Item/MyItem_BP.MyItem_BP_C'"));
	
	if (MI.Succeeded())
	{
		_rewardClass = MI.Class;
	}


	_Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));
	_Widget->SetupAttachment(GetMesh());
	_Widget->SetWidgetSpace(EWidgetSpace::Screen);
	_Widget->SetRelativeLocation(FVector(0.0f, 0.0f, 220.0f));

	static ConstructorHelpers::FClassFinder <UUserWidget> hpBar
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PB_HPBar.PB_HPBar_C'"));

	if (hpBar.Succeeded())
	{
		_Widget->SetWidgetClass(hpBar.Class);
	}
}

void AMyMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMyMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_Widget->InitWidget();
	auto hpBar = Cast<UMyHpBar>(_Widget->GetUserWidgetObject());

	if (hpBar)
	{
		_statCom->_PlHPDelegate.AddUObject(hpBar, &UMyHpBar::SetHpBarvalue);
	}

}

void AMyMonster::DropReword()
{
	if (_rewardClass)
    {
        FVector Location = GetActorLocation();
        const int32 NumItemsToSpawn = 3;

        for (int32 i = 0; i < NumItemsToSpawn; i++)
        {
			float randFloat = FMath::FRandRange(0, PI * 2.0f);
			float X = cosf(randFloat) * 300.0f;
			float Y = sinf(randFloat) * 300.0f;
			Location.Z = 0.0f;
			FVector itemPos = Location + FVector(X, Y, 150.0f);

            GetWorld()->SpawnActor<AMyItem>(_rewardClass, itemPos, FRotator::ZeroRotator);
        }
    }
}

void AMyMonster::Disable()
{
	DropReword();

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if (controller)
		GetController()->UnPossess();
}

void AMyMonster::Attack_AI()
{
	
}

float AMyMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{	
	AMyPlayer* player = Cast<AMyPlayer>(DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);
	if (this->_statCom->IsDead() && player != nullptr)
	{
		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
		player->_statCom->AddExp(GetExp());
	}

	return 0.0f;
}



