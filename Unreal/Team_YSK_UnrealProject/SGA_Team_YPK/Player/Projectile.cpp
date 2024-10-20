// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyMonster.h"
#include "MyPlayer.h"
#include "MyArcher.h"
#include "Engine/DamageEvents.h"
#include "MyGameInstance.h"
#include "MyEffectManager.h"
#include "MySoundManager.h"

#include "TimerManager.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    _meshCom = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm(
    TEXT("/Game/SKnight_modular/Skeleton_Knight_07/mesh/weapon/SK_Arrow.SK_Arrow"));
    if (sm.Succeeded())
    {
        _meshCom->SetSkeletalMesh(sm.Object);
    }

    FRotator MeshRotation = FRotator(-90.f, -90.f, 0.f);  
    _meshCom->SetRelativeRotation(MeshRotation);

    _collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
    _collider->InitCapsuleSize(70.f, 20.f);


    FRotator CapsuleRotation = FRotator(0.f, 0.f, 90.f);  
    _collider->SetRelativeRotation(CapsuleRotation);


    _movementCom = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMove"));

    RootComponent = _meshCom;

    _collider->SetupAttachment(_meshCom);
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    Init();

    GetWorldTimerManager().SetTimer(_timerHandle, this, &AProjectile::Disable, 1.5f, false);

}

void AProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_collider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnMyCharacterOverlap);
}


void AProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AProjectile::FireInDirection(const FVector& ShootDirection)
{
    if (_movementCom)
    {
        _movementCom->Velocity = ShootDirection * _movementCom->InitialSpeed;
    }
}

void AProjectile::OnMyCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromWeep, const FHitResult& SweepResult)
{
    auto monster = Cast<AMyMonster>(OtherActor);
	if (monster)
	{
        FDamageEvent DamageEvent;
        AController* EventInstigator = GetInstigatorController();

        if (_archer != nullptr)
        {
            AActor* DamageCauser = Cast<AActor>(_archer);

            monster->TakeDamage(_damage, DamageEvent, EventInstigator, DamageCauser);

            FVector hitPos = OtherActor->GetActorLocation();
            
            FVector direction = _archer->GetActorForwardVector(); 
            FRotator hitRotation = direction.Rotation();


           if (EffectManager)
            {
                EffectManager->Play("ky_stab", hitPos, hitRotation);
                SoundManager->PlaySound("MyArcher_Hit_Sound", hitPos);
            }
              
        }
		
	}
    else 
    {
        FVector missLocation = GetActorLocation();
        SoundManager->PlaySound("MyArcher_SwingArrow", missLocation);
    }
    
    auto player = Cast<AMyPlayer>(OtherActor);
    Disable();

}

void AProjectile::Init()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

void AProjectile::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
    GetWorldTimerManager().ClearTimer(_timerHandle);
}
