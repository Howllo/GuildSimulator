// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMisc/GuildSimEnums.h"
#include "OverworldPlayerCharacter.generated.h"

#pragma region Class
class UCameraComponent;
class USpringArmComponent;
class UNiagaraComponent;
class UInventorySystem;
class UCharacterStatistic;
class AItem_DefaultActor;
class UEquipmentSystem;
class UCharacterStatistic;
#pragma endregion 

UCLASS()
class GUILDSIMULATOR_API AOverworldPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOverworldPlayerCharacter();

	TEnumAsByte<ECharacterType> CharType;
	
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
	
	/**
	 * @brief Used to set the players name.
	 * @param Name - Takes in a FText to set a FText name.
	 */
	void SetPlayerName(FText Name);
	
	/**
	 * @brief Used to get the players name.
	 * @return Returns the player name through FText.
	 */
	FText GetPlayerName();

	/**
	 * @brief Used to set the gender of the character.
	 * @param Gender - Takes in a FText to set a FText gender.
	 */
	void SetPlayerGender(FText Gender);

	/**
	 * @brief Used to get the characters gender.
	 * @return - Returns a FText of the character gender.
	 */
	FText GetPlayerGender();

	/**
	 * @brief This is used for throwing items from player.
	 * @return Return the scene component of player throw point.
	 */
	USceneComponent* GetSpawnPoint() const;

	/**
	 * @brief Used to get the inventory from the character.
	 * @return Returns the UInventorySystem object from the character.
	 */
	UFUNCTION(BlueprintCallable)
	UInventorySystem* GetInventorySystem() const;

	/**
	 * @brief Use to get the equipment system from the character.
	 * @return Returns UEquipmentSystem object from the character.
	 */
	UFUNCTION(BlueprintCallable)
	UEquipmentSystem* GetPlayerEquipment() const;

	/**
	 * @brief Used to get the stats from the character.
	 * @return Returns the UCharacterStatistics from the character.
	 */
	UFUNCTION(BlueprintCallable)
	UCharacterStatistic* GetCharStats();
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character System", meta=(AllowPrivateAccess="true"))
	UCharacterStatistic* CharStats;
	
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnPoint;
};
