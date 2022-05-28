// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OverworldPlayerCharacter.generated.h"

#pragma region Class
class UCameraComponent;
class USpringArmComponent;
class UNiagaraComponent;
class UInventorySystem;
class UCharacterStatistic;
class AItem_DefaultActor;
class UEquipmentSystem;
#pragma endregion 

UCLASS()
class GUILDSIMULATOR_API AOverworldPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOverworldPlayerCharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UNiagaraComponent* ParticleComponent;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE UCameraComponent* GetCharacterCamera() const { return CameraComp; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
	//Hide all object in between character and camera.
	void CheckForActorCollision();
	
	//Character Name
	void SetPlayerName(FText Name);
	FText GetPlayerName();

	//Character Gender
	void SetPlayerGender(FText Gender);
	FText GetPlayerGender();

	/**
	 * @brief This is used for throwing items from player.
	 * @return Return the scene component of player throw point.
	 */
	USceneComponent* GetSpawnPoint() const;
	
	//Returns the inventory from the player.
	UFUNCTION(BlueprintCallable)
	UInventorySystem* GetInventorySystem() const;

	UEquipmentSystem* GetPlayerEquipment() const;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Character System")
	FText PlayerName;

	UPROPERTY(EditDefaultsOnly, Category="Character System")
	FText CharacterGender;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character System", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character System", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character System", meta=(AllowPrivateAccess = "true"))
	UInventorySystem* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character System", meta=(AllowPrivateAccess="true"))
	UEquipmentSystem* PlayerEquipment;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnPoint;
};
