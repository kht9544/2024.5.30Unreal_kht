// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC.h"
#include "MyNPCStoreUI.h"
#include "Components/WidgetComponent.h"
#include "MyNPCStoreUI.h"
#include "MyNPCAIController.h"
#include "MyAnim_Monster_Instance.h"
#include "MyPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"

//test
#include "MyHpBar.h"

#include "MyWeapon.h"


AMyNPC::AMyNPC()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> np
	(TEXT("/Script/Engine.SkeletalMesh'/Game/SKnight_modular/Skeleton_Knight_07/mesh/SK_SKnight_07_full.SK_SKnight_07_full'"));

	if (np.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(np.Object);

	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FClassFinder<UMyNPCStoreUI> store
	(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/UI/NPCStoreUI_BP.NPCStoreUI_BP_C'"));

	if (store.Succeeded())
	{
		_storeWidget = CreateWidget<UMyNPCStoreUI>(GetWorld(), store.Class);
	}

	AIControllerClass = AMyNPCAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AMyNPC::BeginPlay()
{
	Super::BeginPlay();

	if (_storeWidget)
	{
		_storeWidget->AddToViewport(10);  
		_storeWidget->SetVisibility(ESlateVisibility::Hidden);
		_storeWidget->bIsFocusable = true;
	}

	FName WeaponSocket(TEXT("weapon"));
	CurWeapon = GetWorld()->SpawnActor<AMyWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (nullptr != CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, WeaponSocket);
		CurWeapon->SetActorHiddenInGame(false); 

	}
   

}

void AMyNPC::NPCStoreUI(bool UImark)
{

	if (_storeWidget)
	{
		if (UImark)
		{
			_storeWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		}
		else
		{
			_storeWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void AMyNPC::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	_statCom->SetNPCLevelAndInit(1);

	_aiController = Cast<AMyNPCAIController>(GetController());

	_animInstance = Cast<UMyAnim_Monster_Instance>(GetMesh()->GetAnimInstance());
	if (_animInstance->IsValidLowLevelFast())
	{
		_animInstance->OnMontageEnded.AddDynamic(this, &AMyCreature::OnAttackEnded);
		_animInstance->_attackDelegate.AddUObject(this, &AMyCreature::Attackhit);
		_animInstance->_RemoveDelegate.AddUObject(this, &AMyNPC::WeaponMove);
	}


}

float AMyNPC::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);


	AMyPlayer* player = Cast<AMyPlayer>(DamageCauser);

	float damaged = -_statCom->AddCurHp(-Damage);
	if (this->_statCom->IsDead() && player != nullptr)
	{
		SetActorEnableCollision(false);
		auto controller = GetController();
		if (controller)
			GetController()->UnPossess();
	}

	if (_animInstance != nullptr)
	{
		_animInstance->PlayRemovAnim();

	
	}

	// test
	if (auto NpcController = Cast<AMyNPCAIController>(GetController()))
	{
		if (NpcController && NpcController->GetBlackboardComponent())
		{
			NpcController->GetBlackboardComponent()->SetValueAsBool(FName(TEXT("IsDamaged")), true);
		}
	}

	return damaged;
}

void AMyNPC::Attack_AI()
{

	if (_statCom->IsDead())
	{
		FVector missLocation = GetActorLocation();
		return;
	}

	if (_isAttcking == false && _animInstance != nullptr)
	{
		_animInstance->PlayAttackMontage();
		_isAttcking = true;

		_curAttackIndex %= 3;
		_curAttackIndex++;

		_animInstance->JumpToSection(_curAttackIndex);
	}
}

void AMyNPC::WeaponMove()
{
	FName HandSocket(TEXT("hand_sw")); 

	if (CurWeapon)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, HandSocket);
		CurWeapon->SetActorHiddenInGame(false);
	}
}
