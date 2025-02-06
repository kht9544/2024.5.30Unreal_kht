#include "MyPlayer.h"

#include "Base/MyGameInstance.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/InventoryComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraShakeBase.h"
#include "EnhancedInputComponent.h"
#include "../Monster/NormalMonster.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "UI/SkillWidget.h"
#include "MeteorDecal.h"
#include "Fireball.h"
#include "Kismet/KismetMathLibrary.h"

#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "UI/MiniMapWidget.h"

#include "GameFramework/Actor.h"

#include "../Animation/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/ProgressBar.h"

#include "../Base/Managers/SoundManager.h"
#include "../Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"

#include "UI/PlayerBarWidget.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	_lowerBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerSkeletal"));
	_shoulderBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderSkeletal"));
	_swordBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SwordSkeletal"));
	_shieldBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldSkeletal"));

	_springArm->SetupAttachment(RootComponent);
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> USM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Face_Pos.Free_Body_Face_Pos'"));
	if (USM.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(USM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> LSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Bottom_Pos.Free_Body_Bottom_Pos'"));
	if (LSM.Succeeded())
	{
		_lowerBodyMesh->SetSkeletalMesh(LSM.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SHSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Arms_Pos.Free_Body_Arms_Pos'"));
	if (SHSM.Succeeded())
	{
		_shoulderBodyMesh->SetSkeletalMesh(SHSM.Object);
	}

	_lowerBodyMesh->SetupAttachment(GetMesh());
	_shoulderBodyMesh->SetupAttachment(GetMesh());
	_swordBodyMesh->SetupAttachment(GetMesh());
	_shieldBodyMesh->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/CamerShake_BP.CamerShake_BP_C'"));
	if (CS.Succeeded())
	{
		_cameraShakeClass = CS.Class;
	}

	static ConstructorHelpers::FClassFinder<AMeteorDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/MeteorDecal_Test_BP.MeteorDecal_Test_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
	}

	static ConstructorHelpers::FClassFinder<AFireball> FB(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/FireBall_02_BP.FireBall_02_BP_C'"));
	if (FB.Succeeded())
	{
		_fireball = FB.Class;
	}
	static ConstructorHelpers::FClassFinder<ADecalActor> DA(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/SkillRangeDecal_BP.SkillRangeDecal_BP_C'"));
	if (DA.Succeeded())
	{
		SkillDecalActor = DA.Class;
	}

	static ConstructorHelpers::FClassFinder<ADecalActor> TA(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/TeleportDecal_BP.TeleportDecal_BP_C'"));
	if (TA.Succeeded())
	{
		_teleportDecal = TA.Class;
	}

	_dashDistance = 1000.f;
	_dashSpeed = 3000.f;
	bIsDashing = false;
	DashDuration = _dashDistance / _dashSpeed;
	DashTimeElapsed = 0.f;
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	UIManager->OpenUI(UI_LIST::PlayerBar);
	UIManager->OpenUI(UI_LIST::Skill);
	UIManager->SetPlayerUI(_StatCom);

	SkillOnCooldown.Init(false, 4);

	InitializeDecalPool();
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_KnightanimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_KnightanimInstance->_deathDelegate.AddUObject(this, &ACreature::Disable);
		_KnightanimInstance->_comboDelegate.AddUObject(this, &AMyPlayer::NextCombo);
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_StatCom->IsDead())
		return;

	UpdateCamera(DeltaTime);
}

float AMyPlayer::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	
	if (_StatCom->IsDead())
	{
		UMyGameInstance *GameInstance = Cast<UMyGameInstance>(GetGameInstance());
		if (GameInstance)
		{
			UIManager->CloseAll();
			UIManager->OpenUI(UI_LIST::Load);
			GameInstance->SavePlayerStats(_StatCom);
			GameInstance->SaveInventory(_inventoryComponent);
			GameInstance->SavePlayerSkeletal(this);
			FName Map = TEXT("NewMap");
			UGameplayStatics::OpenLevel(GetWorld(), Map);
		}
	}
	return 0.0f;
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyPlayer::JumpA);
		EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &AMyPlayer::AttackA);
		EnhancedInputComponent->BindAction(_skill1Action, ETriggerEvent::Started, this, &AMyPlayer::Skill1);
		EnhancedInputComponent->BindAction(_skill2Action, ETriggerEvent::Started, this, &AMyPlayer::Skill2);
		EnhancedInputComponent->BindAction(_skill3Action, ETriggerEvent::Started, this, &AMyPlayer::Skill3);
		EnhancedInputComponent->BindAction(_skill4Action, ETriggerEvent::Started, this, &AMyPlayer::Skill4);
		EnhancedInputComponent->BindAction(_mouseAction, ETriggerEvent::Triggered, this, &AMyPlayer::Mouse);
		EnhancedInputComponent->BindAction(_StatOpenAction, ETriggerEvent::Started, this, &AMyPlayer::StatUIOpen);
		EnhancedInputComponent->BindAction(_InvenOpenAction, ETriggerEvent::Started, this, &AMyPlayer::InvenUIOpen);
		EnhancedInputComponent->BindAction(_guardAction, ETriggerEvent::Started, this, &AMyPlayer::GuardStart);
		EnhancedInputComponent->BindAction(_guardAction, ETriggerEvent::Completed, this, &AMyPlayer::GuardEnd);
		EnhancedInputComponent->BindAction(_LockOnAction, ETriggerEvent::Started, this, &AMyPlayer::LockOn);
		EnhancedInputComponent->BindAction(_InteractAction, ETriggerEvent::Started, this, &AMyPlayer::Interect);

		EnhancedInputComponent->BindAction(_OptionsAction, ETriggerEvent::Started, this, &AMyPlayer::OptionsOpen);
	}
}

void AMyPlayer::OnMonsterHit(class AMonster *HitMonster, const FHitResult &Hit)
{
	if (HitMonster)
	{
		FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		HitMonster->LaunchFromPlayer(LaunchDirection);
	}
}

void AMyPlayer::UpdateCamera(float DeltaTime)
{
	if (_lockOnMonster)
	{
		if (_lockOnMonster->GetStatComponent()->IsDead())
		{
			_lockOnMonster = nullptr;
			_fixedCamera = false;
			return;
		}
		_fixedCamera = true;

		FVector LockedOnLocation = _lockOnMonster->GetActorLocation();
		LockedOnLocation.Z -= 150.f;
		const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockedOnLocation);
		const FRotator InterpRotation = UKismetMathLibrary::RInterpTo(GetController()->GetControlRotation(), LookAtRotation, DeltaTime, 10.f);
		GetController()->SetControlRotation(FRotator(InterpRotation.Pitch, InterpRotation.Yaw, GetController()->GetControlRotation().Roll));
	}
}

void AMyPlayer::GetItem(ABaseItem *item)
{
	if (item == nullptr)
		return;
	_inventoryComponent->AddItem(0, item);
}

void AMyPlayer::Silent()
{
	LockAllSkill();

	FTimerHandle TimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AMyPlayer::UnLockAllSkill,
		3.0f,
		false);
}

void AMyPlayer::LockAllSkill()
{
	UIManager->GetSkillUI()->LockAllSkill();
}

void AMyPlayer::UnLockAllSkill()
{
	UIManager->GetSkillUI()->UnLockAllSkill();
}

void AMyPlayer::OnAttackEnded(UAnimMontage *Montage, bool bInterrupted)
{
	_isAttacking = false;

	_curAttackIndex = 1;
}

void AMyPlayer::NextCombo()
{
	_isAttacking = false;
}

void AMyPlayer::EquipBaseBody()
{
	USkeletalMesh *LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Face_Pos.Free_Body_Face_Pos'")));
	if (LoadedMesh)
	{
		GetMesh()->SetSkeletalMesh(LoadedMesh);
	}
}

void AMyPlayer::EquipBaseLower()
{
	USkeletalMesh *LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Bottom_Pos.Free_Body_Bottom_Pos'")));
	if (LoadedMesh)
	{
		_lowerBodyMesh->SetSkeletalMesh(LoadedMesh);
	}
}

void AMyPlayer::EquipBaseShoulder()
{
	USkeletalMesh *LoadedMesh = Cast<USkeletalMesh>(StaticLoadObject(USkeletalMesh::StaticClass(), nullptr, TEXT("/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/Free_WhiteTiger_Detach/Free_Body_Arms_Pos.Free_Body_Arms_Pos")));
	if (LoadedMesh)
	{
		_shoulderBodyMesh->SetSkeletalMesh(LoadedMesh);
	}
}

void AMyPlayer::Move(const FInputActionValue &value)
{
	if (_isGuarding)
		return;
	FVector2D MovementVector = value.Get<FVector2D>();

	_moveVector = MovementVector;

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AMyPlayer::Look(const FInputActionValue &value)
{
	if (_fixedCamera)
		return;
	FVector2D LookAxisVector = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMyPlayer::JumpA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (!_isAttacking)
			ACharacter::Jump();
	}
}

void AMyPlayer::AttackA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (bIsSkillReadyToCast)
		{
			bIsSkillReadyToCast = false;

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateDecal);

			if (SpawnedDecalActor)
			{
				SpawnedDecalActor->Destroy();
				SpawnedDecalActor = nullptr;
			}

			ConfirmSkillLocation();
			return;
		}

		if (bIsTeleportReadyToCast)
		{
			bIsTeleportReadyToCast = false;

			GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateDecal);

			if (SpawnedDecalTeleport)
			{
				SpawnedDecalTeleport->Destroy();
				SpawnedDecalTeleport = nullptr;
			}
			ConfirmTeleportLocation();
			return;
		}
	}

	if (isPressed && _isAttacking == false && _KnightanimInstance != nullptr)
	{
		if (_isGuarding)
			_isGuarding = false;

		_isAttacking = true;

		if (_curAttackIndex < 5)
		{
			_KnightanimInstance->PlayAttackMontage();
			_KnightanimInstance->JumpToSection(_curAttackIndex);
			_curAttackIndex++;
		}

		else if (_curAttackIndex >= 5)
		{
			_KnightanimInstance->PlayAttackMontage();
			_curAttackIndex = 1;
			_KnightanimInstance->JumpToSection(_curAttackIndex);
		}
	}
}

void AMyPlayer::Skill1(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && UIManager->GetSkillUI() != nullptr)
	{
		if (SkillOnCooldown[0] || UIManager->GetSkillUI()->IsSkillLocked(0) || _StatCom->GetCurMp() < 10)
			return;
		else
		{
			SkillOnCooldown[0] = true;
			_StatCom->SetMp(_StatCom->GetCurMp() - 10);

			if (_StatCom->GetInt() >= 40)
			{
				APlayerController *PlayerController = Cast<APlayerController>(GetController());

				if (SpawnedDecalTeleport)
				{
					bIsTeleportReadyToCast = false;
					SpawnedDecalTeleport->Destroy();
					SpawnedDecalTeleport = nullptr;
					PlayerController->bShowMouseCursor = false;
					PlayerController->SetInputMode(FInputModeGameOnly());
					return;
				}

				if (_teleportDecal && !SpawnedDecalTeleport)
				{
					SpawnedDecalTeleport = GetWorld()->SpawnActor<ADecalActor>(_teleportDecal);
					if (SpawnedDecalActor)
					{
						SpawnedDecalActor->SetLifeSpan(0);
					}
				}

				if (PlayerController)
				{
					bool bIsCursorVisible = PlayerController->bShowMouseCursor;
					PlayerController->bShowMouseCursor = true;
					PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
				}

				bIsTeleportReadyToCast = true;

				GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateDecal, this, &AMyPlayer::UpdateTeleportLocation, 0.01f, true);
			}
			else
			{
				FVector2D MovementInput = _moveVector;

				if (MovementInput.IsNearlyZero())
				{
					DashDirection = GetActorForwardVector();
				}
				else
				{
					FVector Forward = GetActorForwardVector() * MovementInput.Y;
					FVector Right = GetActorRightVector() * MovementInput.X;
					DashDirection = (Forward + Right).GetSafeNormal();
				}

				DashTimeElapsed = 0.f;

				SoundManager->PlaySound(*GetSoundName(ESoundType::SkillSound01), _hitPoint);
				DefaultGroundFriction = GetCharacterMovement()->GroundFriction;
				DefaultBrakingDecelerationWalking = GetCharacterMovement()->BrakingDecelerationWalking;

				GetCharacterMovement()->GroundFriction = 0.f;
				GetCharacterMovement()->BrakingDecelerationWalking = 0.f;

				const float DashPower = 1500.f;
				bIsDashing = true;
				LaunchCharacter(DashDirection * DashPower, true, true);

				FTimerHandle DashResetTimerHandle;
				GetWorldTimerManager().SetTimer(DashResetTimerHandle, this, &AMyPlayer::ResetDashFriction, 0.5f, false);
				UIManager->GetSkillUI()->StartCooldown(0, 5.0f);
			}
		}
	}
}

void AMyPlayer::ResetDashFriction()
{
	GetCharacterMovement()->GroundFriction = DefaultGroundFriction;
	GetCharacterMovement()->BrakingDecelerationWalking = DefaultBrakingDecelerationWalking;

	bIsDashing = false;
}

void AMyPlayer::UpdateTeleportLocation()
{
	AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController && SpawnedDecalTeleport)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			if (HitResult.ImpactNormal.Z > 0.5f)
			{
				FVector NewLocation = HitResult.ImpactPoint;
				TargetSkillLocation = NewLocation;
				TargetSkillLocation.Z += 1.0f;

				SkillRotation = HitResult.ImpactNormal.Rotation();
				SpawnedDecalTeleport->SetActorLocation(TargetSkillLocation);
				SpawnedDecalTeleport->SetActorRotation(SkillRotation);
			}
		}
	}
}

void AMyPlayer::ConfirmTeleportLocation()
{
	_StatCom->AddCurMp(-10);
	AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController)
	{
		TargetSkillLocation.Z += 100.f;
		SetActorLocation(TargetSkillLocation);
		EffectManager->Play(*GetSoundName(ESoundType::PlayerSkillEffect04Start), GetActorLocation());

		bIsTeleportReadyToCast = false;

		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());

		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateTeleprotDecal);

		if (UIManager->GetSkillUI())
		{
			UIManager->GetSkillUI()->StartCooldown(0, 5.0f);
		}
	}
}

AMeteorDecal* AMyPlayer::GetPooledMeteorDecal()
{
	for (AMeteorDecal* Meteor : MeteorDecalPool)
    {
        if (Meteor && Meteor->IsHidden())
        {
            return Meteor;
        }
    }

    AMeteorDecal* NewMeteor = GetWorld()->SpawnActor<AMeteorDecal>(AMeteorDecal::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
    if (NewMeteor)
    {
        MeteorDecalPool.Add(NewMeteor);
    }
    return NewMeteor;
}


void AMyPlayer::Skill2(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (SkillOnCooldown[1] || UIManager->GetSkillUI()->IsSkillLocked(1) || _StatCom->GetCurMp() < 10)
			return;

		if (UIManager->GetSkillUI() != nullptr)
		{
			APlayerController *PlayerController = Cast<APlayerController>(GetController());

			if (SpawnedDecalActor)
			{
				bIsSkillReadyToCast = false;
				SpawnedDecalActor->Destroy();
				SpawnedDecalActor = nullptr;
				PlayerController->bShowMouseCursor = false;
				PlayerController->SetInputMode(FInputModeGameOnly());
				return;
			}

			if (SkillDecalActor && !SpawnedDecalActor)
			{
				SpawnedDecalActor = GetWorld()->SpawnActor<ADecalActor>(SkillDecalActor);
				if (SpawnedDecalActor)
				{
					SpawnedDecalActor->SetLifeSpan(0);
				}
			}

			if (PlayerController)
			{
				bool bIsCursorVisible = PlayerController->bShowMouseCursor;
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
			}

			bIsSkillReadyToCast = true;

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_UpdateDecal, this, &AMyPlayer::UpdateDecalLocation, 0.01f, true);
		}
	}
}

void AMyPlayer::UpdateDecalLocation()
{
	AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController && SpawnedDecalActor)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		if (HitResult.bBlockingHit)
		{
			if (HitResult.ImpactNormal.Z > 0.5f)
			{
				FVector NewLocation = HitResult.ImpactPoint;
				TargetSkillLocation = NewLocation;
				TargetSkillLocation.Z += 1.0f;

				SkillRotation = HitResult.ImpactNormal.Rotation();
				SpawnedDecalActor->SetActorLocation(TargetSkillLocation);
				SpawnedDecalActor->SetActorRotation(SkillRotation);
			}
		}
	}
}

void AMyPlayer::ConfirmSkillLocation()
{
	if (SkillOnCooldown[1])
        return;

    _StatCom->AddCurMp(-10);
    SkillOnCooldown[1] = true;

	AMyPlayerController *PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetInputMode(FInputModeGameOnly());
	}
    FVector MeteorStartLocation = GetActorLocation() + FVector(0, 0, 5000.0f);
    FVector DecalLocation = TargetSkillLocation;
    FRotator DecalRotation = SkillRotation;
    DecalRotation.Pitch -= 90.0f;

    int MeteorCount = (_StatCom->GetInt()) / 10;

    AMeteorDecal* CenterMeteorDecal = GetPooledMeteorDecal();
    if (CenterMeteorDecal)
    {
         CenterMeteorDecal->SetActorHiddenInGame(false);
         CenterMeteorDecal->SetActorEnableCollision(true);
         CenterMeteorDecal->StartMeteor(MeteorStartLocation, DecalLocation, 3.0f);
    }

    for (int i = 0; i < MeteorCount - 1; i++)
    {
        float Angle = (i * (360.0f / (MeteorCount - 1))) * (PI / 180.0f);
        float Radius = 900.0f;

        FVector SpawnLocation = DecalLocation;
        SpawnLocation.X += FMath::Cos(Angle) * Radius;
        SpawnLocation.Y += FMath::Sin(Angle) * Radius;

        AMeteorDecal* MeteorDecal = GetPooledMeteorDecal();
        if (MeteorDecal)
        {
            MeteorDecal->SetActorHiddenInGame(false);
            MeteorDecal->SetActorEnableCollision(true);
            MeteorDecal->StartMeteor(MeteorStartLocation, SpawnLocation, 3.0f);
        }
    }

    UIManager->GetSkillUI()->StartCooldown(1, 5.0f);

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlaySkill02Montage();
	}

	SoundManager->PlaySound(*GetSoundName(ESoundType::SkillSound02), _hitPoint);
}

AFireball* AMyPlayer::GetPooledFireball()
{
	for (AFireball* Fire : FireballPool)
    {
        if (Fire && Fire->IsHidden())
        {
            return Fire;
        }
    }

    AFireball* Fireball = GetWorld()->SpawnActor<AFireball>(_fireball, FVector::ZeroVector, FRotator::ZeroRotator);
    if (Fireball)
    {
        FireballPool.Add(Fireball);
    }

    return Fireball;
}

void AMyPlayer::Skill3(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && UIManager->GetSkillUI() != nullptr)
	{
		if (SkillOnCooldown[2] || UIManager->GetSkillUI()->IsSkillLocked(2) || _StatCom->GetCurMp() < 10)
			return;
		else
		{
			_StatCom->AddCurMp(-10);
			SkillOnCooldown[2] = true;
			UIManager->GetSkillUI()->StartCooldown(2, 5.0f);
			if (_fireball != nullptr)
			{
				SoundManager->PlaySound(*GetSoundName(ESoundType::SkillSound03), this->GetActorLocation());
				SoundManager->PlaySound(*GetSoundName(ESoundType::SkillSound03Shout), this->GetActorLocation());

				UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
				if (PlayerAnimInstance)
				{
					PlayerAnimInstance->PlaySkill03Montage();
				}

				int FireballCount = _StatCom->GetInt() / 10;
				FRotator spawnRotation = GetActorRotation();

				for (int i = 0; i < FireballCount; i++)
				{
					float Angle = (i * (360.0f / FireballCount)) * (PI / 180.0f);
					float Radius = 500.0f;

					FVector spawnLocation = GetActorLocation() + GetActorForwardVector() * 50.0f;
					spawnLocation.X += FMath::Cos(Angle) * Radius;
					spawnLocation.Y += FMath::Sin(Angle) * Radius;
					AFireball *Fireball = GetPooledFireball();

					if (Fireball)
					{
						Fireball->SetActorHiddenInGame(false);
            			Fireball->SetActorEnableCollision(true);
						Fireball->InitializeOrbit(Radius, Angle, FireballCount);

						FTimerHandle HideTimerHandle; 
						GetWorld()->GetTimerManager().SetTimer(HideTimerHandle, Fireball, &AFireball::HideFireball, 5.0f, false);
					}
					

				}
			}
		}
	}
}

void AMyPlayer::Skill4(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && UIManager->GetSkillUI() != nullptr)
	{
		if (SkillOnCooldown[3] || UIManager->GetSkillUI()->IsSkillLocked(3) || _StatCom->GetCurMp() < 10)
			return;
		else
		{
			_StatCom->AddCurMp(-10);
			_StatCom->SetStatBoost(_StatCom->GetInt());

			SkillOnCooldown[3] = true;
			UIManager->GetSkillUI()->StartCooldown(3, 10.0f);

			EffectManager->PlayOnSkeletalMesh(*GetSoundName(ESoundType::PlayerSkillEffect04Start), _lowerBodyMesh, "root");
			SoundManager->PlaySound(*GetSoundName(ESoundType::SkillSound04Start), GetActorLocation());

			EffectManager->PlayOnSkeletalMesh(*GetSoundName(ESoundType::PlayerSkillEffect04Durring), _lowerBodyMesh, "root");
			SoundManager->PlaySoundWithDuration(*GetSoundName(ESoundType::SkillSound04Durring), GetActorLocation(), 5.0f);
		}
	}
}

void AMyPlayer::Mouse(const FInputActionValue &value)
{
	APlayerController *PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController)
	{
		bool bIsCursorVisible = PlayerController->bShowMouseCursor;

		if (bIsCursorVisible)
		{
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
		else
		{
			PlayerController->bShowMouseCursor = true;
			PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
		}
	}
}

void AMyPlayer::GuardEnd(const FInputActionValue &value)
{
	_isGuarding = false;

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(_isGuarding);
	}
}

void AMyPlayer::LockOn(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (_lockOnMonster)
		{
			_lockOnMonster = nullptr;
			_fixedCamera = false;
			return;
		}
		else
		{
			FHitResult HitResult;
			FVector Start = GetActorLocation();
			FVector ForwardVector = GetActorForwardVector();
			float LockOnDistance = 2000.0f;
			float LockOnAngle = 60.0f;
			float HalfAngle = LockOnAngle / 2.0f;

			for (float AngleOffset = -HalfAngle; AngleOffset <= HalfAngle; AngleOffset += 5.0f)
			{
				FQuat Rotation = FQuat::MakeFromEuler(FVector(0.0f, 0.0f, AngleOffset));
				FVector End = Start + (Rotation.RotateVector(ForwardVector) * LockOnDistance);

				FCollisionQueryParams CollisionParams;
				CollisionParams.bTraceComplex = true;
				CollisionParams.AddIgnoredActor(this);
				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams))
				{
					AMonster *monster = Cast<AMonster>(HitResult.GetActor());
					if (monster != nullptr)
					{
						_lockOnMonster = monster;
						break;
					}
				}
			}
		}
	}
}

void AMyPlayer::GuardStart(const FInputActionValue &value)
{
	_isGuarding = true;

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(_isGuarding);
	}
}

void AMyPlayer::StatUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto statUI = UIManager->GetStatUI();
	SoundManager->PlaySound(*GetSoundName(ESoundType::UIBaseSound), GetActorLocation());

	if (isPressed && statUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Stat);
	}
}

void AMyPlayer::InvenUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto invenUI = UIManager->GetInventoryUI();
	SoundManager->PlaySound(*GetSoundName(ESoundType::UIBaseSound), GetActorLocation());

	if (isPressed && invenUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Inventory);
	}
}

void AMyPlayer::Interect(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto invenUI = UIManager->GetInventoryUI();

	if (isPressed && invenUI != nullptr)
	{
		interectNPC.Broadcast();
	}
}

void AMyPlayer::OptionsOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto OptionsUI = UIManager->GetOptionsUI();

	if (isPressed && OptionsUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Options);
	}
}

void AMyPlayer::InitializeDecalPool()
{
	for (int32 i = 0; i < MeteorPoolSize; ++i)
    {
        AMeteorDecal* Meteor = GetWorld()->SpawnActor<AMeteorDecal>(_decal, FVector::ZeroVector, FRotator::ZeroRotator);
        if (Meteor)
        {
            Meteor->SetActorHiddenInGame(true);
            Meteor->SetActorEnableCollision(false);
            MeteorDecalPool.Add(Meteor);
        }
    }

	for (int32 i = 0; i < FireballPoolSize; ++i)
    {
        AFireball* Fireball = GetWorld()->SpawnActor<AFireball>(_fireball, FVector::ZeroVector, FRotator::ZeroRotator);
        if (Fireball)
        {
            Fireball->SetActorHiddenInGame(true);
            Fireball->SetActorEnableCollision(false);
            FireballPool.Add(Fireball);
        }
    }
}



void AMyPlayer::StartScreenShake()
{
	static float InitialShakeStrength = 0.1f;
	static float MaxShakeStrength = 10.0f;
	static float IncreaseAmount = 3.0f;
	static float Duration = 1.0f;
	static float ElapsedTime = 0.0f;

	if (_cameraShakeClass)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, InitialShakeStrength);
	}

	ElapsedTime += GetWorld()->GetDeltaSeconds();

	float CurrentShakeStrength = FMath::Lerp(InitialShakeStrength, MaxShakeStrength, FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f));

	if (ElapsedTime < Duration)
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, CurrentShakeStrength);
	}
	else
	{
		UGameplayStatics::GetPlayerCameraManager(this, 0)->StartCameraShake(_cameraShakeClass, MaxShakeStrength * 2.0f);
		GetWorld()->GetTimerManager().ClearTimer(ScreenShakeTimerHandle);
		ElapsedTime = 0.0f;
	}
}



