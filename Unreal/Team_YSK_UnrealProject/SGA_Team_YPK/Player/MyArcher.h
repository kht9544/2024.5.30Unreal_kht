#pragma once

#include "CoreMinimal.h"
#include "MyPlayer.h"
#include "MyArcher.generated.h"

UCLASS()
class SGA_TEAM_YPK_API AMyArcher : public AMyPlayer
{
	GENERATED_BODY()

public:
	AMyArcher();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack_AI() override;

	virtual void Attack(const FInputActionValue& value) override;
	
	void ShootArrow();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> _projectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Stat, meta = (AllowPrivateAccess = "true"))
	class UMyAnim_Archer_Instance* _ArcheranimInstance;
};
