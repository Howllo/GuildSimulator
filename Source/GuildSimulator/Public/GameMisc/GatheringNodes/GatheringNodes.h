// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameMisc/GuildSimEnums.h"
#include "GatheringNodes.generated.h"

class USphereComponent;

UCLASS()
class GUILDSIMULATOR_API AGatheringNodes : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGatheringNodes();
	
	UPROPERTY(EditAnywhere, Category=Node, meta=(AllowPrivateAccess="true"))
	USphereComponent* CollisionSphere;
	
	UPROPERTY(VisibleAnywhere, Category=Node)
	int32 TotalHitPoints;

	UPROPERTY(EditAnywhere, Category=Node)
	float TotalRespawnTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<WeaponType> RequiredWeapon;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<GameRarity> Rarity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent;

	//UPROPERTY(EditAnywhere)
	//TODO:Animation	
	
	UPROPERTY()
	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditAnywhere, Category=Node)
	bool bIsActive = true;

	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
