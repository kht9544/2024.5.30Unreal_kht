#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "MyAnimInstance.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"
#include "MyItem.h"
#include "MyInventoryComponent.h"
#include "MyStatComponent.h"
#include "Components/WidgetComponent.h"
#include "MyGameModeBase.h"
#include "MyHpBar.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonSevarog/Characters/Heroes/Sevarog/Meshes/Sevarog.Sevarog'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	_springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// 카메라 설정
	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength = 500.0f;
	_springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

	RootComponent = GetCapsuleComponent();

	//Stat
	_statCom = CreateDefaultSubobject<UMyStatComponent>(TEXT("Stat"));

	//Inventory
	_InventoryCom = CreateDefaultSubobject<UMyInventoryComponent>(TEXT("Invnetory"));

	//Widget
	_hpbarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HpBar"));

	_hpbarWidget->SetupAttachment(GetMesh());
	_hpbarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	_hpbarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 280.0f));

	static ConstructorHelpers::FClassFinder<UUserWidget>hpBar(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/MyHpBar_BP.MyHpBar_BP_C'"));
	if (hpBar.Succeeded())
	{
		_hpbarWidget->SetWidgetClass(hpBar.Class);
	}


	
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Init();

}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	_animInstance = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (_animInstance->IsValidLowLevel())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCharacter::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCharacter::AttackHit);
	}
	_statCom->SetLevelAndInit(_level);
	//_statCom->_hpChangedDelegate.Add()
	
	_hpbarWidget->InitWidget();
	auto hpBar = Cast<UMyHpBar>(_hpbarWidget->GetUserWidgetObject());

	if (hpBar)
	{
		_statCom->_hpChangedDelegate.AddUObject(hpBar, &UMyHpBar::SetHpBarValue);
	}
}
	

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::JumpA);

		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::AttackA);
	
		//EnhancedInputComponent->BindAction(_dropAction, ETriggerEvent::Started, this, &AMyCharacter::Drop);

		EnhancedInputComponent->BindAction(_dropAction, ETriggerEvent::Started, this, &AMyCharacter::PickItem);
	
		EnhancedInputComponent->BindAction(_openInventoryAction, ETriggerEvent::Started, this, &AMyCharacter::OpenInventory);

	}
}

float AMyCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// TODO:
	// 1. hp - Damage
	// 2. 공격자 이름 출력
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);

	return damaged;
}

void AMyCharacter::AddAttackDamage(AActor* actor, int amount)
{
	_statCom->AddAttackDamage(amount);
}

void AMyCharacter::OnAttackEnded(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG(LogTemp, Error, TEXT("Attack End"));
	_isAttacking = false;
}

void AMyCharacter::AttackHit()
{
	// 공격 충돌 처리
	// TODO:
	// 1. 히튼스캔으로 공격, attackRange는 본인 마음
	// 2. debugdraw까지
	FHitResult hitResult;
	FCollisionQueryParams params(NAME_None, false, this);

	float attackRange = 500.0f;
	float attackRadius = 50.0f;

	bool bResult = GetWorld()->SweepSingleByChannel(
		hitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * attackRange,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(attackRadius),
		params
	);

	FVector vec = GetActorForwardVector() * attackRange;
	FVector center = GetActorLocation() + vec * 0.5f;

	FColor drawColor = FColor::Green;

	if (bResult && hitResult.GetActor()->IsValidLowLevel())
	{
		drawColor = FColor::Red;

		// 피해 처리
		FDamageEvent DamageEvent;
		hitResult.GetActor()->TakeDamage(_statCom->GetAttackDamage(), DamageEvent, GetController(), this);
	
	}
	DrawDebugSphere(GetWorld(), center, attackRadius, 12, drawColor, false, 2.0f);
}

void AMyCharacter::AddItem(AMyItem* item)
{
	_InventoryCom->AddItem(item);
}

void AMyCharacter::DropItem()
{
	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetActorLocation();
	playerPos.Z -= GetActorLocation().Z;

	FVector itemPos = playerPos + FVector(X, Y, 0.0f);

	_InventoryCom->DropItem(itemPos);

}


void AMyCharacter::Move(const FInputActionValue& value)
{
	FVector2D MovementVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookAxisVector = value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMyCharacter::JumpA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	if (isPressed)
	{
		ACharacter::Jump();
	}
}

void AMyCharacter::AttackA(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	if (isPressed && !_isAttacking && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttacking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
	}
}

void AMyCharacter::Drop(const FInputActionValue& value)
{
	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetActorLocation();
	playerPos.Z -= GetActorLocation().Z;

	FVector itemPos = playerPos + FVector(X, Y, 0.0f);

	_InventoryCom->DropItem(itemPos);
}

void AMyCharacter::OpenInventory(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	if (isPressed)
	{
		if (!IsOpenInventory)
		{
			_InventoryCom->OpenInventory();
			IsOpenInventory = true;
		}
			

		else
		{
			_InventoryCom->CloseInventory();
			IsOpenInventory = false;
		}
		
	}
	
}

void AMyCharacter::PickItem(const FInputActionValue& value)
{
	bool isPressed = value.Get<bool>();
	if (isPressed)
	{
		CanPickItem = true;
		UE_LOG(LogTemp, Warning, TEXT("CanPickItem :%d"), CanPickItem);
	}
	
}

void AMyCharacter::Init()
{
	_statCom->Reset();
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::Disable()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;
}
