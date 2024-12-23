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
#include "UI/SkillWidget_test.h"
#include "UI/SkillWidget.h"
#include "MeteorDecal.h"
#include "Fireball.h"
#include "Kismet/KismetMathLibrary.h"

// chelo
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"
#include "UI/StatWidget.h"
#include "Components/WidgetComponent.h"

// MiniMap
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "UI/MiniMapWidget.h"

// te
#include "GameFramework/Actor.h"

// Animation
#include "../Animation/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// hp
#include "Components/ProgressBar.h"

#include "../Base/Managers/SoundManager.h"
#include "../Base/Managers/EffectManager.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Components/AudioComponent.h"
#include "Components/DecalComponent.h"

#include "Player/Dragon.h"

#include "UI/StatWidget.h"
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

	//_upperBodyMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperSkeletal"));
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

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SWSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/WhiteTiger_Detach/Sward_Pos.Sward_Pos'"));
	// if (SWSM.Succeeded())
	// {
	// 	_swordBodyMesh->SetSkeletalMesh(SWSM.Object);
	// }

	// static ConstructorHelpers::FObjectFinder<USkeletalMesh> SSM(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Source/WhiteTiger_Detach/Shield_Pos.Shield_Pos'"));
	// if (SSM.Succeeded())
	// {
	// 	_shieldBodyMesh->SetSkeletalMesh(SSM.Object);
	// }

	_lowerBodyMesh->SetupAttachment(GetMesh());
	_shoulderBodyMesh->SetupAttachment(GetMesh());
	_swordBodyMesh->SetupAttachment(GetMesh());
	_shieldBodyMesh->SetupAttachment(GetMesh());

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	//_parkourComp = CreateDefaultSubobject<UParkourComponent_Test>(TEXT("ParkourComponent"));

	static ConstructorHelpers::FClassFinder<UStatWidget> StatClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerStat_UI.PlayerStat_UI_C'"));
	if (StatClass.Succeeded())
	{
		_statWidget = CreateWidget<UStatWidget>(GetWorld(), StatClass.Class);
	}

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

	static ConstructorHelpers::FClassFinder<UUserWidget> PlBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerBar_UI.PlayerBar_UI_C'"));
	if (PlBar.Succeeded())
	{
		WidgetClass = PlBar.Class;
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

	if (WidgetClass)
	{
		_Widget = CreateWidget<UPlayerBarWidget>(GetWorld(), WidgetClass);
		if (_Widget)
		{
			_Widget->AddToViewport();
		}
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

	if (_statWidget)
	{
		_statWidget->AddToViewport(10);

		_statWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	AMyPlayerController *MyController = Cast<AMyPlayerController>(GetController());
	if (MyController != nullptr)
	{
		_skillWidgetInstance = MyController->SkillWidgetInstance;
	}
	SkillOnCooldown.Init(false, 4);

	if (DragonClass)
	{
		// DragonClass가 설정되었으면 DragonInstance를 생성
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		// 드래곤 인스턴스 스폰
		_dragonInstance = GetWorld()->SpawnActor<ADragon>(DragonClass, SpawnLocation, SpawnRotation, SpawnParams);
	}
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (_Widget)
	{
		auto PlWidget = Cast<UPlayerBarWidget>(_Widget);
		if (PlWidget)
		{
			float CurrentHP = _StatCom->GetCurHp();
			float CurrentMP = _StatCom->GetCurMp();
			float CurrentEXP = _StatCom->GetExp();

			UE_LOG(LogTemp, Warning, TEXT("Current HP: %f, Current MP: %f, Current EXP: %f"), CurrentHP, CurrentMP, CurrentEXP);

			_StatCom->_PlHPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlHPBar);
			_StatCom->_PlMPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlMPBar);
			_StatCom->_PlEXPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlExpBar);
			_StatCom->_PlMaxHPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetMaxHpBar);
			_StatCom->_PlMaxMPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetMaxMpBar);
		}
	}

	_KnightanimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_KnightanimInstance->_deathDelegate.AddUObject(this, &AMyPlayer::Disable);
		_KnightanimInstance->_comboDelegate.AddUObject(this, &AMyPlayer::NextCombo);
		
		/*_KnightanimInstance->_changeDelegate.AddUObject(this, &AMyPlayer::EndMontage);*/
		//_KnightanimInstance->_endMontageDelegate.AddDynamic(this, &AMyPlayer::TransformToDragon);
	}
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_StatCom->IsDead())
		return;

	UpdateCamera(DeltaTime);

	if (bIsDashing)
	{
		PerformDash(DeltaTime);
	}


}

float AMyPlayer::TakeDamage(float Damage, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{

	FVector AttackDirection = DamageCauser->GetActorLocation() - GetActorLocation();
	AttackDirection.Z = 0.0f;
	AttackDirection.Normalize();

	FVector GuardDirection = GetActorForwardVector();

	float DotProduct = FVector::DotProduct(GuardDirection, AttackDirection);
	float Angle = FMath::Acos(DotProduct) * (180.0f / PI);

	const float GuardAngle = 90.0f;

	if (bIsGuarding && Angle <= GuardAngle)
	{
		SoundManager->PlaySound(*GetGuardOn(), _hitPoint);
	}
	else
	{
		UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			AnimInstance->PlayHitReactionMontage();
		}

		SoundManager->PlaySound(*GetGuardOff(), _hitPoint);

		FVector KnockbackDirection = GetActorLocation() - DamageCauser->GetActorLocation();
		KnockbackDirection.Z = 0.0f;
		KnockbackDirection.Normalize();
		LaunchCharacter(KnockbackDirection * 1000.f, true, true);
		_StatCom->AddCurHp(-Damage);

		if (_StatCom->IsDead())
		{
			SoundManager->PlaySound(*GetDeadSoundName(), this->GetActorLocation());

			SetActorEnableCollision(false);
			auto controller = GetController();
			if (controller)
				GetController()->UnPossess();

			GetWorld()->GetTimerManager().SetTimer(TimerHandle_Destroy, this, &ACreature::DelayedDestroy, 2.0f, false);

			UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());
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
		EnhancedInputComponent->BindAction(_Change, ETriggerEvent::Started, this, &AMyPlayer::ToggleTransformation);

	
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
		if (_lockOnMonster->_StatCom->IsDead())
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
        false
    );
}

void AMyPlayer::LockAllSkill()
{
	_skillWidgetInstance->LockAllSkill();
}

void AMyPlayer::UnLockAllSkill()
{
	_skillWidgetInstance->UnLockAllSkill();
}

void AMyPlayer::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
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

FString AMyPlayer::GetSwingSoundName() const
{
	return "SwingSound_Sword_01";
}

FString AMyPlayer::GetHitSoundName() const
{
	return "TakeSound_Sword_01";
}

FString AMyPlayer::GetGuardOn() const
{
	return "ShieldGuard_On";
}

FString AMyPlayer::GetGuardOff() const
{
	return "ShieldGuard_Off";
}

FString AMyPlayer::GetSkillSound01() const
{
	return "Skill01_Sound";
}

FString AMyPlayer::GetSkillSound02() const
{
	return "Skill02_Sound";
}

FString AMyPlayer::GetSkillParticleEffect02() const
{
	return "NS_Meteor";
}

FString AMyPlayer::GetPlayerAttackHitEffect() const
{
	return "P_Greystone_Novaborn_Primary_Impact";
}

FString AMyPlayer::GetSkillSound03() const
{
	return "Skill03_Sound_Begin_Cue";
}

FString AMyPlayer::GetSkillSound03Shout() const
{
	return "Skill03_Shout";
}

FString AMyPlayer::GetPlayerSkillEffect04_Start() const
{
	return "NS_Skill04_Start";
}

FString AMyPlayer::GetPlayerSkillEffect04_Durring() const
{
	return "NS_Priest_Sphere";
}

FString AMyPlayer::GetSkillSound04Start() const
{
	return "Skill04_Sound_Start";
}

FString AMyPlayer::GetSkillSound04Durring() const
{
	return "Skill04_Sound_02_during";
}

FString AMyPlayer::GetUIBaseSound() const
{
	return "BaseUISound_02_Cue";
}

FString AMyPlayer::GetLevelUpSound() const
{
	return "LevelupSound_Cue";
}

void AMyPlayer::Move(const FInputActionValue &value)
{
	if (bIsGuarding)
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
		if (bIsGuarding)
			bIsGuarding = false;

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

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[0]|| _skillWidgetInstance->IsSkillLocked(0) || _StatCom->GetCurMp() < 10)
			return;
		else
		{
			SkillOnCooldown[0] = true;
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
				_StatCom->SetMp(_StatCom->GetCurMp() - 10);
				bIsDashing = true;

				FVector2D MovementInput = _moveVector;
				UE_LOG(LogTemp, Warning, TEXT("%f"), GetVelocity().Size());

				if (GetVelocity().Size() > 300.f)
				{
					FVector Forward = GetActorForwardVector() * MovementInput.Y;
					FVector Right = GetActorRightVector() * MovementInput.X;
					DashDirection = (Forward + Right).GetSafeNormal();
				}
				else
				{
					DashDirection = GetActorForwardVector();
				}

				DashTimeElapsed = 0.f;
				_skillWidgetInstance->StartCooldown(0, 5.0f);

				UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
				if (PlayerAnimInstance)
				{
					PlayerAnimInstance->PlaySkill01Montage();
				}
				SoundManager->PlaySound(*GetSkillSound01(), _hitPoint);
			}
		}
	}
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
	 AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
    if (PlayerController)
    {
		TargetSkillLocation.Z += 100.f;
        SetActorLocation(TargetSkillLocation);
		EffectManager->Play("NS_Teleport",TargetSkillLocation);

        bIsTeleportReadyToCast = false;

        PlayerController->bShowMouseCursor = false;
        PlayerController->SetInputMode(FInputModeGameOnly());

        GetWorld()->GetTimerManager().ClearTimer(TimerHandle_UpdateTeleprotDecal);

        if (_skillWidgetInstance)
        {
            _skillWidgetInstance->StartCooldown(0, 5.0f); 
        }
	}
}


void AMyPlayer::Skill2(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if (SkillOnCooldown[1]|| _skillWidgetInstance->IsSkillLocked(1)|| _StatCom->GetCurMp() < 10)
			return;

		if (_skillWidgetInstance != nullptr)
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

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

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

	AMeteorDecal *CenterMeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, DecalLocation, DecalRotation, SpawnParams);
	if (CenterMeteorDecal)
	{
		CenterMeteorDecal->StartMeteor(MeteorStartLocation, DecalLocation, 3.0f);
	}

	for (int i = 0; i < MeteorCount - 1; i++)
	{
		float Angle = (i * (360.0f / (MeteorCount - 1))) * (PI / 180.0f);
		float Radius = 900.0f;

		FVector SpawnLocation = DecalLocation;
		SpawnLocation.X += FMath::Cos(Angle) * Radius;
		SpawnLocation.Y += FMath::Sin(Angle) * Radius;

		AMeteorDecal *MeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
		if (MeteorDecal)
		{
			MeteorDecal->StartMeteor(MeteorStartLocation, SpawnLocation, 3.0f);
		}
	}

	_skillWidgetInstance->StartCooldown(1, 5.0f);

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlaySkill02Montage();
	}

	SoundManager->PlaySound(*GetSkillSound02(), _hitPoint);
}

void AMyPlayer::Skill3(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[2] || _skillWidgetInstance->IsSkillLocked(2)|| _StatCom->GetCurMp() < 10)
			return;
		else
		{
			_StatCom->AddCurMp(-10);
			SkillOnCooldown[2] = true;
			_skillWidgetInstance->StartCooldown(2, 5.0f);
			if (_fireball != nullptr)
			{
				SoundManager->PlaySound(*GetSkillSound03(), this->GetActorLocation());
				SoundManager->PlaySound(*GetSkillSound03Shout(), this->GetActorLocation());

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
					AFireball *Fireball = GetWorld()->SpawnActor<AFireball>(_fireball, spawnLocation, spawnRotation);

					if (Fireball)
					{
						Fireball->InitializeOrbit(Radius, Angle, FireballCount);
					}
				}
			}
		}
	}
}

void AMyPlayer::Skill4(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[3]|| _skillWidgetInstance->IsSkillLocked(3)|| _StatCom->GetCurMp() < 10)
			return;
		else
		{
			_StatCom->AddCurMp(-10);
			_StatCom->SetStatBoost(_StatCom->GetInt());

			SkillOnCooldown[3] = true;
			_skillWidgetInstance->StartCooldown(3, 10.0f);

			EffectManager->Play(*GetPlayerSkillEffect04_Start(), GetActorLocation());
			SoundManager->PlaySound(*GetSkillSound04Start(), GetActorLocation());

			EffectManager->PlayOnSkeletalMesh(*GetPlayerSkillEffect04_Durring(), _lowerBodyMesh, "root");
			// SoundManager->PlaySound(*GetSkillSound04Durring(), GetActorLocation());
			// SoundManager->StopSound(*GetSkillSound04Durring());
			SoundManager->PlaySoundWithDuration(*GetSkillSound04Durring(), GetActorLocation(), 5.0f);
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
	bIsGuarding = false;

	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
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
				DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 2.0f, 0, 1.0f);

				if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Pawn, CollisionParams))
				{
					DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f, 0, 1.0f);
					AMonster *monster = Cast<AMonster>(HitResult.GetActor());
					if (monster != nullptr)
					{
						UE_LOG(LogTemp, Warning, TEXT("LockOnMonster"));
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
	bIsGuarding = true;

	// Animation
	UPlayerAnimInstance *PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
	}
}

// cheol
void AMyPlayer::StatUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	SoundManager->PlaySound(*GetUIBaseSound(), GetActorLocation());

	APlayerController *PlayerController = Cast<APlayerController>(GetController());

	if (isPressed && _statWidget != nullptr)
	{
		if (_statWidget->IsVisible())
		{
			if (PlayerController)
			{
				PlayerController->bShowMouseCursor = false;
				PlayerController->SetInputMode(FInputModeGameOnly());
			}
			_statWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			if (PlayerController)
			{
				bool bIsCursorVisible = PlayerController->bShowMouseCursor;
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
			}

			_statWidget->UpdateStatDisplay();
			_statWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMyPlayer::InvenUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	auto invenUI = UIManager->GetInventoryUI();
	SoundManager->PlaySound(*GetUIBaseSound(), GetActorLocation());

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

void AMyPlayer::OptionsOpen(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	auto OptionsUI = UIManager->GetOptionsUI();

	if (isPressed && OptionsUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Options);
		//UIManager->OpenUI(UI_LIST::Options);
	}

}

void AMyPlayer::PerformDash(float DeltaTime)
{
	if (DashTimeElapsed < DashDuration)
	{
		FVector DashVelocity = DashDirection * _dashSpeed * DeltaTime;
		AddActorWorldOffset(DashVelocity, true);

		DashTimeElapsed += DeltaTime;
	}
	else
	{
		bIsDashing = false;
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

void AMyPlayer::ClearSkillTimer()
{
	_skillWidgetInstance->ClearAll();
}

void AMyPlayer::TransformToDragon()
{
	//if (_StatCom)
	//{
	//	_StatCom->SetDragonLevelInit(1);
	//}

	if(!GAMEINSTANCE->GetStage2Clear())
		return;
		
	if (!_dragonInstance)
	{
		// 드래곤 인스턴스 생성
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		// 드래곤 스폰
		_dragonInstance = GetWorld()->SpawnActor<ADragon>(DragonClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (!_dragonInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn DragonInstance!"));
			return;
		}
	}

	// 상태 저장 및 변환 로직
	if (APlayerController *PC = Cast<APlayerController>(GetController()))
	{

		// Dragon 활성화
		_dragonInstance->SetActorHiddenInGame(false);
		_dragonInstance->SetActorEnableCollision(true);

		_dragonInstance->SetActorLocation(GetActorLocation()); // 동일한 위치
		_dragonInstance->SetActorRotation(GetActorRotation()); // 동일한 회전

		// MyPlayer 비활성화
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);

		// 컨트롤 전환
		PC->Possess(_dragonInstance);

		_isTransformed = true;
		_dragonInstance->_isTransformed = true;

		UE_LOG(LogTemp, Warning, TEXT("Transformed to Dragon!"));
	}
}

void AMyPlayer::TransformToHuman()
{
	// Dragon에서 MyPlayer로 복귀
	_dragonInstance->TransformToHuman();
}

void AMyPlayer::ToggleTransformation()
{
	if (!_bCanTransform)
	{
		UE_LOG(LogTemp, Warning, TEXT("Transformation is on cooldown."));
		return;
	}

	if (_isTransformed) // 현재 변환된 상태이면 인간으로 복귀
	{
		TransformToHuman();
	}
	else // 그렇지 않으면 드래곤으로 변환
	{
		UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
		if (AnimInstance)
		{
			// 몽타주 재생
			AnimInstance->PlayChangeMontage();

			// 몽타주 종료 이벤트와 연결
			AnimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::HandleMontageEnd);
			StartTransformationCooldown();
		}
	}
}

void AMyPlayer::HandleMontageEnd(UAnimMontage* Montage, bool bInterrupted)
{
	UPlayerAnimInstance* AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInstance && Montage == AnimInstance->GetChangeMontage())
	{
		if (!bInterrupted && !_isTransformed) // 몽타주가 정상 종료되었고 변환 상태가 아닌 경우
		{
			TransformToDragon();
		}

		// 델리게이트 연결 해제
		AnimInstance->OnMontageEnded.RemoveDynamic(this, &AMyPlayer::HandleMontageEnd);
	}
}

void AMyPlayer::StartTransformationCooldown()
{
	_bCanTransform = false;

	// 타이머 설정
	GetWorldTimerManager().SetTimer(
		_transformCooldownHandle,
		this,
		&AMyPlayer::ResetTransformationCooldown,
		_transformCooldown,
		false
	);
}

void AMyPlayer::ResetTransformationCooldown()
{
	_bCanTransform = true;
}
