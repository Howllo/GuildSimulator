// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentSystem.generated.h"

class UItem;
class AOverworldPlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUILDSIMULATOR_API UEquipmentSystem : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentSystem();

	UFUNCTION(BlueprintCallable)
	int32 GetConsumableCapacity();
	
	UFUNCTION(BlueprintCallable)
	void SetConsumableCapacity(int32 TotalCapacity);
	
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerHelm();

	UFUNCTION(BlueprintCallable)
	void SetPlayerHelm(UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerChest();

	UFUNCTION(BlueprintCallable)
	void SetPlayerChest(UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerHands();

	UFUNCTION(BlueprintCallable)
	void SetPlayerHands(UItem* Item);

	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerLeggings();

	UFUNCTION(BlueprintCallable)
	void SetPlayerLeggings(UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerFeet();

	UFUNCTION(BlueprintCallable)
	void SetPlayerFeet(UItem* Item);

	/**
	 * @brief Returns the ring based on the slot that the player chooses.
	 * @param Slot - The slot that will return. 1 - First Slot. 2 - Second Slot
	 * @return Returns UItem of ring based on the slot.
	 */
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerRing(int32 Slot);

	/**
	 * @brief This is meant to set the gear that the character has.
	 * @param Item - Set the item that is going to be used for adding to the slot.
	 * @param Slot - Slot that the ring will go into. 1 - First Slot. 2 - Second Slot.
	 */
	UFUNCTION(BlueprintCallable)
	void SetPlayerRing(UItem* Item, int32 Slot);

	/**
	 * @brief Returns the trinket based on the slot that the player chooses.
	 * @param Slot - The slot that will return. 1 - First Slot. 2 - Second Slot
	 * @return Returns UItem of Trinket based on the slot.
	 */
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerTrinket(int32 Slot);

	/**
	 * @brief This is meant to set the gear that the character has.
	 * @param Item - Set the item that is going to be used for adding to the slot.
	 * @param Slot - Slot that the trinket will go into. 1 - First Slot. 2 - Second Slot.
	 */
	UFUNCTION(BlueprintCallable)
	void SetPlayerTrinket(UItem* Item, int32 Slot);
	
	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerWeapon();

	UFUNCTION(BlueprintCallable)
	void SetPlayerWeapon(UItem* Item);

	UFUNCTION(BlueprintCallable)
	UItem* GetPlayerOffHand();

	UFUNCTION(BlueprintCallable)
	void SetPlayerOffHand(UItem* Item);
	
	UFUNCTION(BlueprintCallable)
	TArray<UItem*>& GetPlayerConsumables();

	UFUNCTION(BlueprintCallable)
	bool AddPlayerConsumables(UItem* Item);

	UFUNCTION(BlueprintCallable)
	bool RemoveItemFromConsumables(UItem* Item);
	
	/**
	 * @brief Removes the item from player inventory.
	 * @param Item - Send in the GetItem into the parameters to remove the item from the character.
	 * @return Returns the the item object to be binds to a pointer item.
	 */
	bool RemoveArmor(const UItem* Item);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditDefaultsOnly ,Category=Equipment)
	int32 ConsumableCapacity;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerHelm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerChest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerHands;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerLeggings;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerFeet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	TArray<UItem*> PlayerRing;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	TArray<UItem*> PlayerTrinket;
	
	// Do not use for Overworld Character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerWeapon;

	// Do not use for Overworld Character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	UItem* PlayerOffHand;
	
	// Do not use for Overworld Character.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category=Equipment, meta=(AllowPrivateAccess = "true"))
	TArray<UItem*> PlayerConsumables;

	UPROPERTY()
	AOverworldPlayerCharacter* PlayerCharacter;
};

