// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterCharacter.h"
#include "MyInventoryComponent.h"
#include "MonsterAnimInstance.h"

// Sets default values
AMonsterCharacter::AMonsterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> sm(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));

	if (sm.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(sm.Object);
	}
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimBPClass(TEXT("/Script/Engine.AnimBlueprint'/Game/Blueprint/Animation/Monster/MonsterAnimInstance_BP.MonsterAnimInstance_BP_C'"));

	if (AnimBPClass.Succeeded())
	{
		AnimBlueprint = AnimBPClass.Class;
		GetMesh()->SetAnimInstanceClass(AnimBlueprint);
	}

	static ConstructorHelpers::FClassFinder<AMyItem> mi(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/MyItem_BP.MyItem_BP_C'"));
	if (mi.Class != nullptr)
	{
		_myItem = mi.Class;
	}

	//Inventory
	_InventoryCom = CreateDefaultSubobject<UMyInventoryComponent>(TEXT("Invnetory"));

}

// Called when the game starts or when spawned
void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_monsteranimInstance = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	_monsteranimInstance->_deadDelegate.AddUObject(this, &AMonsterCharacter::Dead);	

}

// Called every frame
void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMonsterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float  AMonsterCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	// TODO:
	// 1. hp - Damage
	// 2. 공격자 이름 출력

	_curHp -= Damage;

	if (_curHp <= 0)
	{
		_curHp = 0;
		_isDead = true;
	}
		
	//StartItem();
	UE_LOG(LogTemp, Warning, TEXT("Attack : %s , CurHP : %f"), *DamageCauser->GetName(), _curHp);

	if (_curHp <= 0)
	{
		_monsteranimInstance->PlayDeadMontage();
	}

	return _curHp;
}

void AMonsterCharacter::Dead()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	PrimaryActorTick.bCanEverTick = false;

  	float randFloat = FMath::FRandRange(0, PI * 2.0f);

	float X = cosf(randFloat) * 300.0f;
	float Y = sinf(randFloat) * 300.0f;
	FVector playerPos = GetActorLocation();
	playerPos.Z -= GetActorLocation().Z;

	FVector itemPos = playerPos + FVector(X, Y, 0.0f);

	//_InventoryCom->DropItem(itemPos);

	
}

void AMonsterCharacter::AddItem(AMyItem* item)
{
	_InventoryCom->AddItem(item);
}

void AMonsterCharacter::StartItem()
{
	if (_myItem != nullptr)
	{
		//_InventoryCom->AddItem(_myItem);
		//UE_LOG(LogTemp, Warning, TEXT("add item"));
	}
}
