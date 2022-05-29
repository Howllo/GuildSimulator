// Copyright (c) Astral Games. All right reserved.


#include "Character/OverworldPlayerCharacter.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/CharacterSubsystems/CharacterStatistic.h"
#include "Character/CharacterSubsystems/EquipmentSystem.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AOverworldPlayerCharacter::AOverworldPlayerCharacter()
{
	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//Capsule Component
	GetCapsuleComponent()->InitCapsuleSize(26.f, 96.0f);

	// Character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->GravityScale = 1.35f;
	GetCharacterMovement()->JumpZVelocity += 50.f;

	//Mesh
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -91.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	
	//Character Boom
	CameraBoom= CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SetRelativeRotation(FRotator(315.f,35.f,0.f));
	CameraBoom->bDoCollisionTest = false;

	//Camera
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	CameraComp->bUsePawnControlRotation = false;
	CameraComp->SetFieldOfView(90.f);

	//Particle Effect
	ParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	ParticleComponent->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	ParticleComponent->SetRelativeLocation(FVector(0.f, -21.7f, 125.0f));

	//Inventory System
	Inventory = CreateDefaultSubobject<UInventorySystem>(TEXT("InventoryComp"));
	Inventory->SetBoolPlayerInventory(true);

	// Equipement System
	PlayerEquipment = CreateDefaultSubobject<UEquipmentSystem>(TEXT("EqupmentSystem"));
	
	//Spawn Point
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(GetMesh());
	SpawnPoint->SetRelativeLocation(FVector(-5.f,15.f, 123.7f));

	//Set Defaults
	PlayerName = FText::FromString("Enter Name...");
	CharType = CT_OVERWORLD;
	
	//Set Character Stats
	CharStats = CreateDefaultSubobject<UCharacterStatistic>(TEXT("CharStats"));
}

// Called when the game starts or when spawned
void AOverworldPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	ParticleComponent->Deactivate();
}

// Called every frame
void AOverworldPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOverworldPlayerCharacter::CheckForActorCollision()
{
	FHitResult hit;
	FCollisionQueryParams CollisionParams;
	
	bool WasHit = ActorLineTraceSingle(hit, CameraComp->GetComponentLocation(), GetActorLocation(), ECollisionChannel::ECC_Visibility, CollisionParams);

	if(WasHit)
	{
		AActor* HitActor = hit.GetActor();
		//HitActor->
	}
}

void AOverworldPlayerCharacter::SetPlayerName(FText Name)
{
	PlayerName = Name;
}

FText AOverworldPlayerCharacter::GetPlayerName()
{
	return PlayerName;
}

void AOverworldPlayerCharacter::SetPlayerGender(const FText Gender)
{
	CharacterGender = Gender;
}

FText AOverworldPlayerCharacter::GetPlayerGender()
{
	return CharacterGender;
}

USceneComponent* AOverworldPlayerCharacter::GetSpawnPoint() const
{
	return SpawnPoint;
}


UInventorySystem* AOverworldPlayerCharacter::GetInventorySystem() const
{
	return Inventory;
}

UEquipmentSystem* AOverworldPlayerCharacter::GetPlayerEquipment() const
{
	return PlayerEquipment;
}

UCharacterStatistic* AOverworldPlayerCharacter::GetCharStats()
{
	return CharStats;
}
