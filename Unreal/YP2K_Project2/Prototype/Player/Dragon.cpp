// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Dragon.h"
#include "Base/MyGameInstance.h"
#include "Player/MyPlayer.h"
#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"

#include "../Animation/PlayerAnimInstance.h"
#include "../Animation/DragonAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "../Animation/BaseAnimInstance.h"
#include "Monster/Monster.h"


#include "Base/Managers/UIManager.h"
#include "UI/StatWidget.h"
#include "UI/PlayerBarWidget.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"


ADragon::ADragon()
{
	PrimaryActorTick.bCanEverTick = true;
	_knightInstance = nullptr;
    
    GetCapsuleComponent()->InitCapsuleSize(230.0f, 230.0f);
    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    
    _springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    _camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    
    _springArm->SetupAttachment(RootComponent);
    _camera->SetupAttachment(_springArm);

    _springArm->TargetArmLength = 1200.0f;
    _springArm->SetRelativeRotation(FRotator(-35.0f, 0.0f, 0.0f));

    _springArm->bUsePawnControlRotation = false;
    _camera->bUsePawnControlRotation = false;

    bUseControllerRotationYaw = false;

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> DragonMeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/QuadrapedCreatures/MountainDragon/Meshes/SK_MOUNTAIN_DRAGON.SK_MOUNTAIN_DRAGON'"));
    if (DragonMeshAsset.Succeeded())
    {
        GetMesh()->SetSkeletalMesh(DragonMeshAsset.Object);
    }

    GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -230.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));



    static ConstructorHelpers::FClassFinder<UStatWidget> StatClass(
        TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/PlayerStat_UI.PlayerStat_UI_C'"));
    if (StatClass.Succeeded())
    {
        _statWidget = CreateWidget<UStatWidget>(GetWorld(), StatClass.Class);
    }

    if (WidgetClass)
    {
        _Widget = CreateWidget<UPlayerBarWidget>(GetWorld(), WidgetClass);
        if (_Widget)
        {
            _Widget->AddToViewport();
        }
    }

}

void ADragon::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<AMyPlayer> It(GetWorld()); It; ++It)
    {
        _knightInstance = *It;
        if (_knightInstance)
        {
            break;
        }
    }

    if (!_knightInstance)
    {
        return;
    }
    SetActorHiddenInGame(true);
    SetActorEnableCollision(false);
    bIsTransformed = false;

}




void ADragon::TransformToHuman()
{
     if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        _knightInstance->SetActorLocation(GetActorLocation()); 
        _knightInstance->SetActorRotation(GetActorRotation());

        _knightInstance->SetActorHiddenInGame(false);
        _knightInstance->SetActorEnableCollision(true);

        SetActorHiddenInGame(true);
        SetActorEnableCollision(false);

        PC->Possess(_knightInstance);

        bIsTransformed = false;
        _knightInstance->bIsTransformed = false;

        UE_LOG(LogTemp, Warning, TEXT("Transformed back to MyPlayer!"));
    }

}

void ADragon::TransformToDragon()
{
    _knightInstance->TransformToDragon();
}

void ADragon::ToggleTransformation()
{
    if (bIsTransformed)
    {
        TransformToHuman();
    }
    else 
    {
        TransformToDragon();
    }
}

void ADragon::OnMonsterHit(AMonster* HitMonster, const FHitResult& Hit)
{
    if (HitMonster)
    {
        FVector LaunchDirection = (HitMonster->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        HitMonster->LaunchFromPlayer(LaunchDirection);
    }
}

void ADragon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(_moveAction, ETriggerEvent::Triggered, this, &ADragon::Move);
        EnhancedInputComponent->BindAction(_lookAction, ETriggerEvent::Triggered, this, &ADragon::Look);
        EnhancedInputComponent->BindAction(_jumpAction, ETriggerEvent::Triggered, this, &ADragon::JumpA);
        EnhancedInputComponent->BindAction(_Change, ETriggerEvent::Started, this, &ADragon::ToggleTransformation);
        EnhancedInputComponent->BindAction(_attackAction, ETriggerEvent::Started, this, &ADragon::AttackA);
    
    }
}

void ADragon::Move(const FInputActionValue& value)
{
    FVector2D MovementVector = value.Get<FVector2D>();
           
    if (Controller && MovementVector.Size() > 0.0f)
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(ForwardDirection, MovementVector.Y); 
        AddMovementInput(RightDirection, MovementVector.X); 
    }
}

void ADragon::Look(const FInputActionValue& value)
{
    FVector2D LookAxisVector = value.Get<FVector2D>();

    AddControllerYawInput(LookAxisVector.X); 
    AddControllerPitchInput(LookAxisVector.Y); 

}

void ADragon::JumpA(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();

    if (isPressed)
    {
        if (GetCharacterMovement()->IsFalling())
        {
            FVector ForwardInput = GetActorForwardVector() * GetInputAxisValue("MoveForward");
            FVector RightInput = GetActorRightVector() * GetInputAxisValue("MoveRight");
            FVector JumpImpulse = ForwardInput * 300.0f + RightInput * 300.0f + FVector(0.0f, 0.0f, 500.0f);

            LaunchCharacter(JumpImpulse, true, true);
        }
        else
        {
            ACharacter::Jump();
            GetCharacterMovement()->GravityScale = 0.5f;
            GetCharacterMovement()->AirControl = 0.8f;   
            GetCharacterMovement()->MaxFlySpeed = 800.0f; 
         }
        _dragonAnimInstance->SetJumping(true);
    }
    else
    {
        if (!GetCharacterMovement()->IsFalling())
        {
            GetCharacterMovement()->GravityScale = 1.0f;
            GetCharacterMovement()->AirControl = 0.2f;
            GetCharacterMovement()->MaxFlySpeed = 600.0f;
            _dragonAnimInstance->SetJumping(false);
        }
    }
}

void ADragon::AttackA(const FInputActionValue& value)
{
    bool isPressed = value.Get<bool>();
    if (isPressed && _isAttacking == false && _dragonAnimInstance != nullptr)
    {
        _dragonAnimInstance->PlayAttackMontage();
        _isAttacking = true;

        _curAttackIndex %= 2;
        if (GetCharacterMovement()->IsFalling()) 
        {
            _dragonAnimInstance->JumpToSection(2); 
        }
        else
        {
            _dragonAnimInstance->JumpToSection(1);
        }
    }


}

void ADragon::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    if (DragonAnimInstanceClass)
    {
        USkeletalMeshComponent* MeshComp = GetMesh();
        if (MeshComp)
        {
            MeshComp->SetAnimInstanceClass(DragonAnimInstanceClass);
        }
    }

    _dragonAnimInstance = Cast<UDragonAnimInstance>(GetMesh()->GetAnimInstance());
    if ( _dragonAnimInstance->IsValidLowLevelFast())
    {
        _dragonAnimInstance->OnMontageEnded.AddDynamic(this, &ADragon::OnAttackEnded);


        _dragonAnimInstance->_attackDelegate.AddUObject(this, &ACreature::AttackHit);
  
        _dragonAnimInstance->_deathDelegate.AddUObject(this, &ADragon::Disable);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to initialize _dragonAnimInstance for ADragon!"));
    }
    if (_StatCom)
    {
        _StatCom->SetDragonLevelInit(1);
    }
   
}

void ADragon::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    if (_StatCom->IsDead())
        return;


    if (GetVelocity().Size() > 0.0f)
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw = FMath::Atan2(GetVelocity().Y, GetVelocity().X) * 180.0f / PI; 
        SetActorRotation(NewRotation);
    }

}

float ADragon::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

    Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


    return 0.0f;
}
