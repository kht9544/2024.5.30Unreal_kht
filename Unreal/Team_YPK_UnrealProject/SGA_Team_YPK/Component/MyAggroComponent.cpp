#include "MyAggroComponent.h"
#include "MyPlayer.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyAggroUserWidget.h"

// Sets default values for this component's properties
UMyAggroComponent::UMyAggroComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMyAggroComponent::RegisterDamage(AMyPlayer* Player, float DamageAmount)
{
    if (Player == nullptr) return;

    if (_playerParty.Contains(Player))
    {
        _playerParty[Player] += DamageAmount;
    }
    else
    {
        _playerParty.Add(Player, DamageAmount);
    }

    UpdateUI(_aggroUIWidget);
}

void UMyAggroComponent::UpdateUI(UMyAggroUserWidget* AggroUI)
{
    if (AggroUI == nullptr)
        return;

    float MaxDamage = 0.f;
    for (const auto& AggroEntry : _playerParty)
    {
        if (AggroEntry.Value > MaxDamage)
        {
            MaxDamage = AggroEntry.Value;
        }
    }

    for (auto& player : _playerParty)
    {
        AggroUI->UpdateAllAggroDisplay(player.Key, player.Value, MaxDamage);
    }

    if (GetTopAggroTarget() != nullptr)
    {
        AggroUI->UpdateAggroDisplay(GetTopAggroTarget(), _playerParty[GetTopAggroTarget()], MaxDamage);
    }
}

AMyPlayer* UMyAggroComponent::GetTopAggroTarget() const
{
    AMyPlayer* TopAggroActor = nullptr;
    float MaxDamage = 0.f;

    for (const auto& AggroEntry : _playerParty)
    {
        if (AggroEntry.Key->_statCom->IsDead())
            continue;

        if (AggroEntry.Value > MaxDamage)
        {
            MaxDamage = AggroEntry.Value;
            TopAggroActor = AggroEntry.Key;
        }
    }
    return TopAggroActor;
}

// Called when the game starts
void UMyAggroComponent::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void UMyAggroComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}