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
#include "../UI/SkillWidget_test.h"
#include "MeteorDecal.h"
#include "Kismet/KismetMathLibrary.h"

// chelo
#include "Base/Managers/UIManager.h"
#include "UI/InventoryWidget.h"
#include "UI/StatWidget.h"
#include "Components/WidgetComponent.h"

//MiniMap
#include "GameFramework/Actor.h"
#include "Components/SceneCaptureComponent2D.h"
#include "PaperSpriteComponent.h"
#include "UI/MiniMapWidget.h"

// te
#include "GameFramework/Actor.h"

// Animation
#include "../Animation/PlayerAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/PlayerBarWidget.h"


//hp
#include "Components/ProgressBar.h"

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

	// MiniMap test
	_MiniMapspringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("MiniSpringArm"));
	_MiniMapspringArm->SetupAttachment(RootComponent);
	_MiniMapspringArm->SetWorldRotation(FRotator::MakeFromEuler(FVector(0.0f, -90.0f, 0.0f)));
	_MiniMapspringArm->bUsePawnControlRotation = false;
	_MiniMapspringArm->bInheritPitch = false;
	_MiniMapspringArm->bInheritRoll = false;
	_MiniMapspringArm->bInheritYaw = false;

	_MiniMapCapture = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("MiniCapture"));
	_MiniMapCapture->SetupAttachment(_MiniMapspringArm);

	_MiniMapCapture->ProjectionType = ECameraProjectionMode::Orthographic;
	_MiniMapCapture->OrthoWidth = 1024;

	_MinimapSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapSprite"));
	_MinimapSprite->SetupAttachment(RootComponent);
	_MinimapSprite->SetWorldRotation(FRotator::MakeFromEuler(FVector(90.f, 0.f, -90.f)));
	_MinimapSprite->SetWorldScale3D(FVector(0.5f));
	_MinimapSprite->SetWorldLocation(FVector(0.f, 0.f, 300.f));
	_MinimapSprite->bVisibleInSceneCaptureOnly = true;

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

	// MiniMap
	// static ConstructorHelpers::FClassFinder<UMiniMapWidget> MinuMap(
	// 	TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MiniMap_UI.MiniMap_UI_C'"));

	// if (MinuMap.Succeeded())
	// {
	// 	_MiniMap = CreateWidget<UMiniMapWidget>(GetWorld(), MinuMap.Class);
	// }

	static ConstructorHelpers::FClassFinder<UCameraShakeBase> CS(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/Player/CamerShake_BP.CamerShake_BP_C'"));
	if (CS.Succeeded())
	{
		_cameraShakeClass = CS.Class;
	}

	static ConstructorHelpers::FClassFinder<AMeteorDecal> MD(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/VFX/MeteorDecal_BP.MeteorDecal_BP_C'"));
	if (MD.Succeeded())
	{
		_decal = MD.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlBar
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerBar_UI.PlayerBar_UI_C'"));

	if (PlBar.Succeeded())
	{
		WidgetClass = PlBar.Class;
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

	// Animation : Guard (shield)
	/*GuardStartSectionName = TEXT("GuardStart");  
	GuardEndSectionName = TEXT("GuardEnd");*/
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (_statWidget)
	{
		_statWidget->AddToViewport();
		_statWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (_MiniMap)
	{
		_MiniMap->AddToViewport();
	}



	AMyPlayerController *MyController = Cast<AMyPlayerController>(GetController());
	if (MyController != nullptr)
	{
		_skillWidgetInstance = MyController->SkillWidgetInstance;
	}
	SkillOnCooldown.Init(false, 4);
}


void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

		_StatCom->SetLevelInit(1);


	if (_Widget)
	{
		auto PlWidget = Cast<UPlayerBarWidget>(_Widget);
		if (PlWidget)
		{
			float CurrentHP = _StatCom->GetCurHp();
			float CurrentMP = _StatCom->GetCurMp();
			float CurrentEXP = _StatCom->GetExp();

			// 플레이어 스탯
			UE_LOG(LogTemp, Warning, TEXT("Current HP: %f, Current MP: %f, Current EXP: %f"), CurrentHP, CurrentMP, CurrentEXP);

			_StatCom->_PlHPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlHPBar);
			_StatCom->_PlMPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlMPBar);
			_StatCom->_PlEXPDelegate.AddUObject(PlWidget, &UPlayerBarWidget::SetPlExpBar);
		}

	}

	ItemEquipped.AddDynamic(this,&AMyPlayer::EquipItem);

	_KnightanimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (_KnightanimInstance->IsValidLowLevelFast())
	{
		_KnightanimInstance->OnMontageEnded.AddDynamic(this, &AMyPlayer::OnAttackEnded);
		_KnightanimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
		_KnightanimInstance->_deathDelegate_Knight.AddUObject(this, &AMyPlayer::Disable);
	}


}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDashing)
	{
		PerformDash(DeltaTime);
	}

	if (_Widget)
	{
		auto PlWidget = Cast<UPlayerBarWidget>(_Widget);
		if (PlWidget)
		{
			int32 plMaxHp = _StatCom->GetMaxHp();
			int32 pMaxMp = _StatCom->GetMaxMp();
			float NewHPScaleX = (plMaxHp + 10.0f) / 1000.0f;

			float NewMPScaleX = (pMaxMp + 0.5f) / 50.0f;


			if (_StatCom->GetMaxHp() > _StatCom->GetCurHp())
			{
				PlWidget->Pl_HPBar->SetRenderScale(FVector2D(NewHPScaleX, 3.0f));

			}

			if (_StatCom->GetMaxMp() > _StatCom->GetCurMp())
			{
				PlWidget->Pl_MPBar->SetRenderScale(FVector2D(NewMPScaleX, 3.0f));
			}

		}

	}
}

float AMyPlayer::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

// Called to bind functionality to input
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

void AMyPlayer::EquipItem(AEquipItem* equipitem)
{
	SetEquipItem(equipitem->GetEquipType(),equipitem);
}

void AMyPlayer::GetItem(ABaseItem* item)
{
	if (item == nullptr)
		return;

	_inventoryComponent->AddItem(0, item);
}

void AMyPlayer::SetEquipItem(EItemType equiptype, AEquipItem* equipitem)
{
    if (_EquipItems.Contains(equiptype))
    {
		//TODO 
        return;
    }
    else
    {
        _EquipItems.Add(equiptype, equipitem);
	}
	// TODO:Update UI
}


//void AMyPlayer::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
//{
//	_isAttacking = false;
//}

void AMyPlayer::Move(const FInputActionValue &value)
{
	if(bIsGuarding)
		return;
	FVector2D MovementVector = value.Get<FVector2D>();

	_moveVector = MovementVector;

	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AMyPlayer::Look(const FInputActionValue &value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMyPlayer::JumpA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		if(!_isAttacking)
			ACharacter::Jump();
	}
}

void AMyPlayer::AttackA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttacking == false && _KnightanimInstance != nullptr)
	{
		AttackHit();
		 if(bIsGuarding)
		 	bIsGuarding = false;
		 _KnightanimInstance->PlayAttackMontage();
		 _isAttacking = true;

		 _curAttackIndex %= 4;
		 _curAttackIndex++;

		 _KnightanimInstance->JumpToSection(_curAttackIndex);
	}

}

void AMyPlayer::Skill1(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[0])
			return;
		else
		{
			SkillOnCooldown[0] = true;
			bIsDashing = true;

			FVector2D MovementInput = _moveVector;

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

			UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
			if (PlayerAnimInstance)
			{
				PlayerAnimInstance->PlaySkill01Montage(); 
			}
			
		}
	}
}

void AMyPlayer::Skill2(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();

    if (isPressed && _skillWidgetInstance != nullptr)
    {
        if (SkillOnCooldown[1])
            return;
        else
        {
            SkillOnCooldown[1] = true;

            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();

            FVector MeteorStartLocation = GetActorLocation() + FVector(0, 0, 5000.0f);  // 하늘에서 시작
            FVector DecalLocation = GetActorLocation() + GetActorForwardVector() * 1000.0f;
            DecalLocation.Z -= 98.0f;  

            AMeteorDecal* MeteorDecal = GetWorld()->SpawnActor<AMeteorDecal>(_decal, DecalLocation, FRotator::ZeroRotator, SpawnParams);
            if (MeteorDecal)
            {
                MeteorDecal->StartMeteor(MeteorStartLocation, DecalLocation, 2.0f);
            }

            GetWorld()->GetTimerManager().SetTimer(ScreenShakeTimerHandle, this, &AMyPlayer::StartScreenShake, 0.1f, true);
            GetWorld()->GetTimerManager().SetTimer(MeteorTimerHandle, this, &AMyPlayer::CastMeteor, 3.0f, false); 

            _skillWidgetInstance->StartCooldown(1, 15.0f);


			UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
			if (PlayerAnimInstance)
			{
				PlayerAnimInstance->PlaySkill02Montage();
			}

        }
    }
}

void AMyPlayer::Skill3(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[2])
			return;
		else
		{
			SkillOnCooldown[2] = true;
			_skillWidgetInstance->StartCooldown(2, 5.0f);
		}
	}
}

void AMyPlayer::Skill4(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _skillWidgetInstance != nullptr)
	{
		if (SkillOnCooldown[3])
			return;
		else
		{
			SkillOnCooldown[3] = true;
			_skillWidgetInstance->StartCooldown(3, 10.0f);
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

	UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
	}

}

void AMyPlayer::GuardStart(const FInputActionValue &value)
{
	bIsGuarding = true;

	// Animation
	UPlayerAnimInstance* PlayerAnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (PlayerAnimInstance)
	{
		PlayerAnimInstance->PlayGuardMontage(bIsGuarding);
	}

}


// cheol
void AMyPlayer::StatUIOpen(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	UE_LOG(LogTemp, Error, TEXT("StatUI Errow"));

	if (isPressed && _statWidget != nullptr)
	{
		if (_statWidget->IsVisible())
		{
			_statWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			_statWidget->UpdateStatDisplay();
			_statWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AMyPlayer::InvenUIOpen(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();

	auto invenUI = UIManager->GetInventoryUI();

	if (isPressed && invenUI != nullptr)
	{
		UIManager->ToggleUI(UI_LIST::Inventory);
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

void AMyPlayer::CastMeteor()
{
}

// void AMyPlayer::CheckForClimbableWall()
// {
// 	FVector Start = GetActorLocation();
// 	FVector ForwardVector = GetActorForwardVector();
// 	FVector End = Start + (ForwardVector * 100.0f);

// 	FHitResult HitResult;
// 	FCollisionQueryParams Params;
// 	Params.AddIgnoredActor(this);

// 	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, Params);

// 	if (bHit && HitResult.bBlockingHit)
// 	{
// 		if (!_parkourComp->bIsClimbing)
// 		{
// 			// 벽타기 시작
// 			_parkourComp->StartClimbing(HitResult.ImpactNormal);
// 		}
// 	}
// 	else
// 	{
// 		if (_parkourComp->bIsClimbing)
// 		{
// 			// 벽이 없으므로 벽타기 멈추기
// 			_parkourComp->StopClimbing();
// 		}
// 	}
// }
