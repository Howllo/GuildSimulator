// Copyright (c) Astral Games. All right reserved.

#include "GameMisc/GatheringNodes/GatheringNodes.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
AGatheringNodes::AGatheringNodes()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Static Mesh COmp
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	
	//Sphere Colliders
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGatheringNodes::OnOverlapBegin);
	CollisionSphere->OnComponentEndOverlap.AddDynamic(this, &AGatheringNodes::OnOverlapEnd);

	// Set Stuff
	CurrentHitPoints = TotalHitPoints;
}

// Called when the game starts or when spawned
void AGatheringNodes::BeginPlay()
{
	Super::BeginPlay();
	
	if(!bOverrideBaseStats)
	{
		switch (Rarity)
		{
		case GRarity_Common:
			TotalHitPoints = 30.f;
			TotalRespawnTime = 300.f;
			break;
		case GRarity_Uncommon:
			TotalHitPoints = 100.f;
			TotalRespawnTime = 600.f;
			break;
		case GRarity_Epic:
			TotalHitPoints = 700.f;
			TotalRespawnTime = 1800.f;
			break;
		case  GRarity_Legendary:
			TotalHitPoints = 2500.f;
			TotalRespawnTime = 3600.f;
			break;
		default:
			TotalHitPoints = 30.f;
			TotalRespawnTime = 300.f;
			break;
		}
		CurrentHitPoints = TotalHitPoints;
	}
}

void AGatheringNodes::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(OtherActor);

	//TODO: Switch Tables

}

void AGatheringNodes::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
