// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Monster.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "../Player/MyPlayer.h"
#include "../Player/MyPlayerController.h"
#include "Item/BaseItem.h"
#include "Item/Consumes/ConsumeItem.h"
#include "Item/Equip/EquipItem.h"
#include "Base/MyGameInstance.h"
#include "Animation/BaseAnimInstance.h"
#include "Component/StatComponent.h"

AMonster::AMonster()
{
    GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

    _capsuleComponent = GetCapsuleComponent();
    _capsuleComponent->OnComponentHit.AddDynamic(this, &AMonster::OnHit);
}

void AMonster::BeginPlay()
{
    Super::BeginPlay();
}

void AMonster::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    InitalizeAnim();
}

void AMonster::InitalizeAnim()
{
    _monster_AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
    if (_monster_AnimInstance->IsValidLowLevelFast())
    {
        _monster_AnimInstance->OnMontageEnded.AddDynamic(this, &ACreature::OnAttackEnded);
        _monster_AnimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
        _monster_AnimInstance->_deathDelegate.AddUObject(this, &AMonster::Disable);
    }
}

void AMonster::Disable()
{
    Super::Disable();
    Reward();
     APlayerController *PlayerController = GetWorld()->GetFirstPlayerController();
        AMyPlayer *Player = Cast<AMyPlayer>(PlayerController->GetPawn());
        if (Player)
        {
            Player->GetInventory()->AddMoney(FMath::FRand() * 100);
            Player->GetStatComponent()->AddExp(_StatCom->GetNextExp());
            const float RewardChance = 0.3f;

            if (FMath::FRand() <= RewardChance)
            {
                Player->GetInventory()->AddItemToSlot(_newItem);
            }
        }
}

void AMonster::Attack_AI()
{
    if (_isAttacking)
    {
        return;
    }
    _isAttacking = true;
	RandomSectionIndex = FMath::RandRange(1, 3);
    _monster_AnimInstance->PlayAttackMontage();
    _monster_AnimInstance->JumpToSection(RandomSectionIndex);
}

float AMonster::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    return 0.0f;
}

void AMonster::Reward()
{
    float Random = FMath::FRand();
    float RewardThreshold = 0.5;

    if (Random <= RewardThreshold)
    {
        int RandomItemValue = FMath::RandRange(2, 3);
        auto *ConsumeItem = GetWorld()->SpawnActor<AConsumeItem>(AConsumeItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
        if (ConsumeItem)
        {
            ConsumeItem->SetItemWithCode(RandomItemValue);
            _newItem = ConsumeItem;
        }
    }
    else
    {
        int RandomEquipValue = FMath::RandRange(2, 11);
        auto *EquipItem = GetWorld()->SpawnActor<AEquipItem>(AEquipItem::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
        if (EquipItem)
        {
            EquipItem->SetItemWithCode(RandomEquipValue);
            int32 EquipType = EquipItem->GetEquip();
            EquipItem->SetEquipType(EquipType);
            _newItem = EquipItem;
        }
        _newItem->SetPlayer();
    }
}

void AMonster::LaunchFromPlayer(FVector LaunchDirection)
{
    LaunchCharacter((LaunchDirection * _launchLength) + _upVector, true, true);
}

void AMonster::OnHit(UPrimitiveComponent *HitComponent, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    AMyPlayer *Player = Cast<AMyPlayer>(OtherActor);
    if (Player && Player->IsDashing())
    {
        Player->OnMonsterHit(this, Hit);
    }
}
