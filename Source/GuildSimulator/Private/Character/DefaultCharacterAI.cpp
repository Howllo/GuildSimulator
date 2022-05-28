// Copyright (c) Astral Games. All right reserved.


#include "Character/DefaultCharacterAI.h"

#include "Character/DefaultCharacterAI.h"
#include "GameplayTagContainer.h"
#include "Character/CharacterSubsystems/CharacterStatistic.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ADefaultCharacterAI::ADefaultCharacterAI()
{
	// Activate ticking in order to update cursor;
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	//Character Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->MaxAcceleration = 1000.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.0f;
	this->JumpMaxCount = 0;
	
	//Statistics component
	CharacterStatistic = CreateDefaultSubobject<UCharacterStatistic>(TEXT("StatisticsComp"));

	//Inventory System
	InventorySystem = CreateDefaultSubobject<UInventorySystem>(TEXT("InventoryComp"));
	
	//Arrow Component
	ArrowLeft = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowLeft"));
	ArrowLeft->SetupAttachment(RootComponent);
	ArrowLeft->SetRelativeRotation(FRotator(0.f, 45.f, 0.f));
	ArrowRight = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowRight")); 
	ArrowRight->SetupAttachment(RootComponent);
	ArrowRight->SetRelativeRotation(FRotator(0.f, -45.f, 0.f));
	
	//Collision Sphere
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(50.f);
	//SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefaultCharacterAI::OnOverlapBegin);
	//SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefaultCharacterAI::OnOverlapEnd);
	
	//Character Mesh
	GetMesh()->SetRelativeLocation(FVector(0,0,-89.7)); 
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	//Character CapsuleComp
	GetCapsuleComponent()->SetCapsuleSize(21.5f, 91.f);
	SelectionCaps = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SelectionCaps"));
	SelectionCaps->SetupAttachment(RootComponent);
	SelectionCaps->SetCapsuleSize(5.0f, 5.0f);
	SelectionCaps->SetRelativeLocation(FVector(0,0,0));
	
	//Static Mesh Component :: TODO: Change this out with a glowing circle on the floor showing the selected actors.
	CursorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectionMesh"));
	CursorMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SelectedMesh(TEXT("StaticMesh'/Game/Cursor/SM_CursorMesh.SM_CursorMesh'"));
	if(SelectedMesh.Succeeded())
	{
		CursorMesh->SetStaticMesh(SelectedMesh.Object);
		CursorMesh->SetVisibility(false);
	}
}

// Called when the game starts or when spawned
void ADefaultCharacterAI::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADefaultCharacterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//GetCapsuleComponent()->OnComponentHit
}

bool ADefaultCharacterAI::IsCharacterDead()
{
	if(CharacterStatistic != nullptr)
	{
		if(CharacterStatistic->IsCharacterDead())
		{
			CharacterStateOne = CCS_DEAD;
			return true;
		}
	}
	return false;
}

void ADefaultCharacterAI::CharacterSelected() const
{
	if(CursorMesh)
	{
		CursorMesh->SetVisibility(true);
	}
}

void ADefaultCharacterAI::CharacterNotSelected() const
{
	if(CursorMesh)
	{
		CursorMesh->SetVisibility(false);
	}
}

void ADefaultCharacterAI::PushCharacterOutTheWay(AActor* Collision)
{
	const float PlayerMovement = GetCharacterMovement()->Velocity.Length();

	if(PlayerMovement > 0.0f || PlayerMovement < 0.0f)
	{
		GetCharacterMovement()->JumpOff(Collision);	
	}
}

void ADefaultCharacterAI::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const ADefaultCharacterAI* HolderActor = nullptr;
	
	if(OtherActor)
	{
		HolderActor = Cast<ADefaultCharacterAI>(OtherActor);
	}
	
	if(GetVelocity().Length() > 0.0f || GetVelocity().Length() < 0.0f)
	{
		if(HolderActor && OtherActor)
		{
			if(HolderActor->GetVelocity().Length() == 0.0f)
			{
				const float DistanceLeft = ArrowLeft->GetComponentLocation().Length() - HolderActor->RootComponent->GetComponentLocation().Length();
				const float DistanceRight = ArrowRight->GetComponentLocation().Length() - HolderActor->RootComponent->GetComponentLocation().Length();

				if(DistanceLeft < DistanceRight)
				{
					OtherActor->AddActorLocalOffset(FVector(0.0f,0.0f,0.0f), true);
				} else
				{
					OtherActor->AddActorLocalOffset(FVector(0.0f,0.0f,0.0f), true);	
				}
			}
		}
	}
}

void ADefaultCharacterAI::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}
