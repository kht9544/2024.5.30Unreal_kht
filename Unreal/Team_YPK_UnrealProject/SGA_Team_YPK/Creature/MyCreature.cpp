// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCreature.h"
#include "MyStatComponent.h"
#include "MyInvenComponent.h"
#include "Engine/DamageEvents.h"
#include "MyHpBar.h"
#include "MyPlayer.h"
#include "MyMonster.h"
#include "Components/WidgetComponent.h"
#include "MyGameInstance.h"
#include "MyEffectManager.h"
#include "MySoundManager.h"


// Sets default values
AMyCreature::AMyCreature() : _lastAttackedMonster(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));

	_invenCom = CreateDefaultSubobject<UMyInvenComponent>(TEXT("Inven"));
}

// Called when the game starts or when spawned
void AMyCreature::BeginPlay()
{
	Super::BeginPlay();
}

void AMyCreature::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_statCom->SetLevelAndInit(1);
}

// Called every frame
void AMyCreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyCreature::Attackhit()
{
	FHitResult hitResult;
    FCollisionQueryParams params(NAME_None, false, this);

    float attackRange = 500.0f;
    float attackRadius = 50.0f;

    bool bResult = GetWorld()->SweepSingleByChannel(
        hitResult,
        GetActorLocation(),
        GetActorLocation() + GetActorForwardVector() * attackRange,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(attackRadius),
        params);

    FVector vec = GetActorForwardVector() * attackRange;
    FVector center = GetActorLocation() + vec * 0.5f;

    FColor drawColor = FColor::Green;

    if (bResult)
    {
        drawColor = FColor::Red;

        if (hitResult.GetActor() && hitResult.GetActor()->IsValidLowLevel())
        {
            AMyMonster* attackedMonster = Cast<AMyMonster>(hitResult.GetActor());
            if (attackedMonster != nullptr)
            {
                if (_lastAttackedMonster != nullptr && _lastAttackedMonster != attackedMonster)
                {
                    _lastAttackedMonster->HideHP();
                }
                attackedMonster->ShowHP();
                _lastAttackedMonster = attackedMonster;
            }

            FDamageEvent DamageEvent;
            hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);

            _hitPoint = hitResult.ImpactPoint;
            EffectManager->Play(*GetHitParticleName(), _hitPoint);
            SoundManager->PlaySound(*GetHitSoundName(), _hitPoint);
        }
    }
    else
    {
        FVector missLocation = GetActorLocation();
        SoundManager->PlaySound(*GetSwingSoundName(), missLocation);
    }
}

FString AMyCreature::GetHitParticleName() const
{
	return "default_hit_particle";
}

FString AMyCreature::GetHitSoundName() const
{
	return "default_hit_sound";
}

FString AMyCreature::GetSwingSoundName() const
{
	return "default_SwingAttackSound";
}

FString AMyCreature::GetDeadSoundName() const
{
	return "default_DeadSound";
}

float AMyCreature::TakeDamage(float Damage, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);
	if (_statCom->IsDead())
	{
		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
	}

	return 0.0f;
}

void AMyCreature::OnAttackEnded(UAnimMontage *Montage, bool bInterrupted)
{

	_isAttcking = false;
	_attackEndedDelegate.Broadcast();
}

void AMyCreature::Init()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCreature::Disable()
{
	SetActorHiddenInGame(true);

	PrimaryActorTick.bCanEverTick = false;
	auto controller = GetController();
	if (controller)
		GetController()->UnPossess();
}

void AMyCreature::ShowHP()
{
    if(_screenWidget)
	{
		_screenWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AMyCreature::HideHP()
{
    if(_screenWidget)
	{
		_screenWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
