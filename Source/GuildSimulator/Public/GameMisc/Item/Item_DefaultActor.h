// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_DefaultActor.generated.h"

class UItem;
class USphereComponent;
class UBoxComponent;
class UProjectileMovementComponent;


 //	Base class to create all items for the game until a better system is created. 
UCLASS()
class GUILDSIMULATOR_API AItem_DefaultActor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AItem_DefaultActor();
	
	// Returns the static mesh of the actor.
	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetMesh() const;

	// Return collision sphere information.
	UFUNCTION(BlueprintCallable)
	USphereComponent* GetSphereCollider() const;
	
	// Returns a actor skeleton mesh, used for outfits only.
	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetSkeletonMesh() const;

	// Deletes objects after 5 minutes.
	void CleanUpObject();
	
	UFUNCTION(BlueprintCallable)
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION(BlueprintCallable)
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Default Item that can be replaced.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
	UItem* Item;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category="Item")
	USceneComponent* DefaultRoot;

	UPROPERTY(VisibleAnywhere, Category="Item")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category="Item")
	USkeletalMeshComponent* SkeletalMeshComponent;
	
	UPROPERTY(VisibleAnywhere, Category="Item")
	USphereComponent* CollisionSphere;

	// Use for timing the destruction of actor.
	FTimerHandle TimerHandle;
};
