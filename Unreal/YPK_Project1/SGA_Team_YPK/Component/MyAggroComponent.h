#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyAggroComponent.generated.h"

class AMyPlayer;
class UMyAggroUserWidget;

USTRUCT(BlueprintType)
struct FAggroEntry
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    AMyPlayer* _player;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    float _damage;

    FAggroEntry() : _player(nullptr), _damage(0.f) {}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SGA_TEAM_YPK_API UMyAggroComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyAggroComponent();

	void RegisterDamage(AMyPlayer* Player, float DamageAmount);
	void UpdateUI(UMyAggroUserWidget* AggroUI);

    AMyPlayer* GetTopAggroTarget() const;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "PlayerParty",meta = (AllowPrivateAccess = "true"))
	TMap<AMyPlayer*, float> _playerParty;
	
	UPROPERTY(EditAnywhere, Category = "UI",meta = (AllowPrivateAccess = "true"))
	UMyAggroUserWidget* _aggroUIWidget;

};
