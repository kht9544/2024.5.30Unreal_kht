#pragma once

#include "CoreMinimal.h"
#include "MyPlayer.h"
#include "MyKnight.generated.h"

UCLASS()
class SGA_TEAM_YPK_API AMyKnight : public AMyPlayer
{
	GENERATED_BODY()

public:
	AMyKnight();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FString GetHitParticleName() const override;
	virtual FString GetHitSoundName() const override;
	virtual FString GetSwingSoundName() const override;

	virtual void Attack_AI() override;

	virtual void Attack(const FInputActionValue& value) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_Knight_Instance* _KnightanimInstance;
};
