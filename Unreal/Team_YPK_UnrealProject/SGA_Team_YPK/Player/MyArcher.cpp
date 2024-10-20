// Fill out your copyright notice in the Description page of Project Settings.

#include "MyArcher.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyPlayer.h"
#include "MyAnim_Archer_Instance.h"
#include "Projectile.h"
#include "MyInvenUI.h"

AMyArcher::AMyArcher()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ar(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSparrow/Characters/Heroes/Sparrow/Meshes/Sparrow.Sparrow'"));

	if (ar.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(ar.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AMyArcher::BeginPlay()
{
	Super::BeginPlay();

	SetActorLabel(TEXT("Archer_1"));
}

void AMyArcher::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_ArcheranimInstance = Cast<UMyAnim_Archer_Instance>(GetMesh()->GetAnimInstance());
	if (_ArcheranimInstance->IsValidLowLevelFast())
	{
		_ArcheranimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_ArcheranimInstance->_attackDelegate_Archer.AddUObject(this, &AMyArcher::ShootArrow);
		_ArcheranimInstance->_deathDelegate_Archer.AddUObject(this, &AMyPlayer::Disable);
	}
}

void AMyArcher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyArcher::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyArcher::Attack);
	}
}

void AMyArcher::Attack_AI()
{
	Super::Attack_AI();

	if (_ArcheranimInstance != nullptr)
	{
		_ArcheranimInstance->PlayAttackMontage();
		_isAttcking = true;
	}
}

void AMyArcher::Attack(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttcking == false && _ArcheranimInstance != nullptr)
	{
		_ArcheranimInstance->PlayAttackMontage();
		_isAttcking = true;
	}
}

void AMyArcher::ShootArrow()
{
	if (_projectileClass)
	{
		FVector forward = GetActorForwardVector();
		FVector fireLocation = GetActorLocation() + (forward * 150);

		FRotator fireRotation = forward.Rotation();

		auto projectile = GetWorld()->SpawnActor<AProjectile>(_projectileClass, fireLocation, fireRotation);
		if (projectile)
		{
			projectile->SetArcher(this);
			projectile->SetDamage(_statCom->GetAttackDamage());
			projectile->FireInDirection(forward);
		}
	}
}
