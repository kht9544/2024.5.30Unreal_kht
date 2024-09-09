// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKnight.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyAnim_Knight_Instance.h"

#include "MyInvenUI.h"


AMyKnight::AMyKnight()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> pl
	(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKwang/Characters/Heroes/Kwang/Meshes/Kwang_GDC.Kwang_GDC'"));

	if (pl.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(pl.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));


}

void AMyKnight::BeginPlay()
{
	Super::BeginPlay();

}

void AMyKnight::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_KnightanimInstance = Cast<UMyAnim_Knight_Instance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &AMyCreature::Attackhit);
		_KnightanimInstance->_deathDelegate_Knight.AddUObject(this, &AMyPlayer::Disable);
	}
}

void AMyKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyKnight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyKnight::Attack);
	}


}

void AMyKnight::Attack_AI()
{
	Super::Attack_AI();

	if (_KnightanimInstance != nullptr)
	{
		_KnightanimInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;


		_KnightanimInstance->JumpToSection(_curAttackIndex);
	}
}



void AMyKnight::Attack(const FInputActionValue& value)
{

	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttcking == false && _KnightanimInstance != nullptr)
	{
		_KnightanimInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;


		_KnightanimInstance->JumpToSection(_curAttackIndex);
	}

	
}



FString AMyKnight::GetHitParticleName() const
{
	return "ky_hit_slash";
}

FString AMyKnight::GetHitSoundName() const
{
	return "MyKnight_Hit_Sound";
}

FString AMyKnight::GetSwingSoundName() const
{
	return "MyKnight_Swing";
}
