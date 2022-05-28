// Copyright (c) Astral Games. All right reserved.


#include "GameMisc/Item/Item_DefaultActor.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameMisc/SingleClassCharStats.h"
#include "GameMisc/Item/Item.h"

// Sets default values
AItem_DefaultActor::AItem_DefaultActor()
{
	if(RootComponent == nullptr)
	{
		DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultRoot"));
		SetRootComponent(DefaultRoot);
	}

	// Default Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Assets/BlueprintMissing.BlueprintMissing'"));
	if(MeshObj.Succeeded())
	{
		StaticMesh->SetStaticMesh(MeshObj.Object);
	}
	StaticMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	StaticMesh->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECR_Ignore);
	StaticMesh->SetSimulatePhysics(false);
	
	// Skeleton Mesh
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMEsh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	
	//Collision Sphere
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	CollisionSphere->SetupAttachment(GetMesh());
	CollisionSphere->SetSphereRadius(37.f);
	CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AItem_DefaultActor::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AItem_DefaultActor::OnOverlapEnd);
	
	//Set Default State
	ItemType = IType_NONE;

	// Create a sub-object of item that can be replaced.
	Item = CreateDefaultSubobject<UItem>(TEXT("Item"));
}

// Called when the game starts or when spawned
void AItem_DefaultActor::BeginPlay()
{
	Super::BeginPlay();

	// Load in Information. TODO: Fix this.
	if(Item)
	{
		if(Item->SkeletalMesh)
		{
			GetSkeletonMesh()->SetSkeletalMesh(Item->SkeletalMesh);
			GetMesh()->DestroyComponent();
		}

		if(Item->WorldMesh)
		{
			GetMesh()->SetStaticMesh(Item->WorldMesh);
			GetSkeletonMesh()->DestroyComponent();
		}

		if(Item->ItemType != IType_Weapon || Item->ItemType != IType_Armor)
		{
			Item->CharStats = nullptr;
		}

		if(Item->ItemType != IType_Consumable)
		{
			Item->ConsumableScript = nullptr;
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AItem_DefaultActor::CleanUpObject,300.f, false);
}

UStaticMeshComponent* AItem_DefaultActor::GetMesh() const
{
	return StaticMesh;
}

USphereComponent* AItem_DefaultActor::GetSphereCollider() const
{
	return CollisionSphere;
}

USkeletalMeshComponent* AItem_DefaultActor::GetSkeletonMesh() const
{
	return SkeletalMeshComponent;
}

void AItem_DefaultActor::CleanUpObject()
{
	this->Destroy();
}

void AItem_DefaultActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOverworldPlayerCharacter* PlayerChar = Cast<AOverworldPlayerCharacter>(OtherActor);
	if(PlayerChar)
	{
		if(Item)
		{
			const bool bCheckAdd = PlayerChar->GetInventorySystem()->AddItem(Item);

			if(Item->Quantity == 0 || bCheckAdd)
			{
				Destroy();
			}
		}
	}
}

void AItem_DefaultActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}