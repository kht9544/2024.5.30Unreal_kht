// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "MyAnimInstance.h"
#include "Engine/DamageEvents.h"

#include "MyStatComponent.h"
#include "MyInvenComponent.h"

#include "MyAnim_Knight_Instance.h"
#include "MyAnim_Archer_Instance.h"

#include "MyInvenUI.h"
#include "Components/WidgetComponent.h"

#include "MyNPC.h"
#include "MyNPCStoreUI.h"
#include "Kismet/GameplayStatics.h"
#include "MyNPCItem.h"

#include "MyPlayerWidget.h"

AMyPlayer::AMyPlayer() : _money(20)
{
	RootComponent = GetCapsuleComponent();

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UMyInvenUI> invenClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MyInvenUI_BP.MyInvenUI_BP_C'"));

	if (invenClass.Succeeded())
	{
		auto temp = invenClass.Class;

		_invenWidget = CreateWidget<UMyInvenUI>(GetWorld(), invenClass.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> PlBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerBar_BP.PlayerBar_BP_C'"));

	if (PlBar.Succeeded())
	{
		WidgetClass = PlBar.Class;
	}
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StoreNPC)
	{
		float Distance = FVector::Dist(GetActorLocation(), StoreNPC->GetActorLocation());

		if (Distance > InteractionDistance)
		{
			StoreNPC->NPCStoreUI(false);
		}
	}

}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (_invenWidget)
	{
		_invenWidget->AddToViewport(5);
		_invenWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (WidgetClass)
	{
		_screenWidget = CreateWidget<UMyPlayerWidget>(GetWorld(), WidgetClass);
		if (_screenWidget)
		{
			_screenWidget->AddToViewport();
			_screenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	auto PlWidget = Cast<UMyPlayerWidget>(_screenWidget);
	if (PlWidget)
	{
		_statCom->_PlHPDelegate.AddUObject(PlWidget, &UMyPlayerWidget::SetPlHPBar);
		_statCom->_PlEXPDelegate.AddUObject(PlWidget, &UMyPlayerWidget::SetPlExpBar);
		_statCom->_PILevelDelegate.AddUObject(PlWidget, &UMyPlayerWidget::SetPlLevel);
	}
}

void AMyPlayer::SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);

		EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);

		EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Started, this, &AMyPlayer::JumpA);

		EnhancedInputComponent->BindAction(_InventoryAction, ETriggerEvent::Started, this, &AMyPlayer::Inven);

		EnhancedInputComponent->BindAction(_mouseAction, ETriggerEvent::Triggered, this, &AMyPlayer::Mouse);

		EnhancedInputComponent->BindAction(_itemDropAction, ETriggerEvent::Started, this, &AMyPlayer::DropItemFromCharacter);

		EnhancedInputComponent->BindAction(_interactionAction, ETriggerEvent::Started, this, &AMyPlayer::Interaction);
	}
}

void AMyPlayer::Disable()
{
	Super::Disable();
}

void AMyPlayer::Move(const FInputActionValue &value)
{
	FVector2D MovementVector = value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		_vertical = MovementVector.Y;
		_horizontal = MovementVector.X;

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyPlayer::Look(const FInputActionValue &value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AMyPlayer::JumpA(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed)
	{
		ACharacter::Jump();
	}
}

void AMyPlayer::Inven(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _invenWidget)
	{
		if (_invenWidget->IsVisible())
		{
			_invenWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			_invenWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
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

void AMyPlayer::Interaction(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	StoreNPC = Cast<AMyNPC>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyNPC::StaticClass()));
	float Distance = FVector::Dist(GetActorLocation(), StoreNPC->GetActorLocation());
	if (StoreNPC)
	{
		if (Distance <= InteractionDistance)
		{
			if (isPressed)
			{
				bool bIsVisible = StoreNPC->_storeWidget->IsVisible();
				StoreNPC->NPCStoreUI(!bIsVisible);
			}
		}
	}
}

void AMyPlayer::Attack(const FInputActionValue &value)
{
	bool isPressed = value.Get<bool>();

	if (isPressed && _isAttcking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttcking = true;
		_curAttackIndex %= 3;
		_curAttackIndex++;
		_animInstance->JumpToSection(_curAttackIndex);
	}
}

void AMyPlayer::AddAttackDamage(AActor *actor, int amount)
{
	_statCom->AddAttackDamage(amount);
}

void AMyPlayer::AddItemToCharacter(class AMyNPCItem *item)
{
	_invenCom->AddItem(item);
}

void AMyPlayer::DropItemFromCharacter()
{
	_invenCom->DropItem();
}
