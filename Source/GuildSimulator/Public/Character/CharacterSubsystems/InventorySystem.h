// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameMisc/GuildSimEnums.h"
#include "GameMisc/Item/Item.h"
#include "InventorySystem.generated.h"

#pragma region Class
class UItem;
class AItem_DefaultActor;
class UInventoryUI;
class UUniformGridPanel;
class UInventorySlot;
class AOverworldHUD;
#pragma endregion

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventorySlotUpdate, TEnumAsByte<EItemType>, Type);

/**
 * Inventory System component deals with adding and removing, and handles the inventory items. This will also
 * handle 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUILDSIMULATOR_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()
public:
	// Sets default values for this component's properties
	UInventorySystem();

	UPROPERTY(BlueprintAssignable)
	FInventorySlotUpdate InventorySlotUpdate;
	
	/**
	 * @brief Takes in a outfit item to store it in a OutfitArray. Used for display and to use items for characters.
	 * @param Item Item
	 * @return Bool
	 */
	UFUNCTION(BlueprintCallable)
	bool AddItem(UItem* Item);
	
	/**
	 * @brief Remove items from the inventory based on UItem parent class.
	 * @param Item UItem
	 * @return Return a false if cannot find it or return true if it can and was deleted.
	 */
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(const UItem* Item);

	/**
	 * @brief This function purpose to to create new actor and item class to be dropped into the world.
	 * @param Item - The base item that will be dropped into the world.
	 * @param Amount - The total quantity of items that will be dropped.
	 */
	UFUNCTION(BlueprintCallable)
	void DropItem(UItem* Item, const int32 Amount);
	
	/**
	 * @brief This sets the bIsPlayerInventory to determine which route to take when it comes to storing
	 *		information.
	 * @param SetPlayerB Takes in a boolean to set another boolean.
	 */
	void SetBoolPlayerInventory(bool SetPlayerB);

	/**
	 * @brief Update the inventory UI slots.
	 * @param Type Takes in a ItemType enum to determine what inventory slots to update.
	 */
	void UpdateInventory(const EItemType Type);

	/**
	 * @brief The point of the function is to set the individual slots in the TMap.
	 * @param Type - Send in a enum ItemType to get the proper slot.
	 * @param Capacity Sets the location slot of the map to capacity. This only set one slot.
	 */
	UFUNCTION(BlueprintCallable)
	void SetCapacity(EItemType Type, const int32 Capacity);

	/**
	 * @brief Used to check if the capacity has been reach in any of the inventory slots.
	 * @return Return the capacity as a TMap.
	 */
	TMap<EItemType, int32>& GetCapacity(); // Warning this cannot be UFUNCTION

	/**
	 * @brief Returns the current selected slot.
	 * @return Returns SelectedSlots.
	 */
	UFUNCTION(BlueprintCallable)
	UInventorySlot* GetSelectedSlot() const;
	
	/**
	 * @brief Purpose to set the Selected Slot.
	 * @param Slot Set the slot selected slot item with the inputted.
	 */
	UFUNCTION(BlueprintCallable)
	void SetSelectedSlot(UInventorySlot* Slot);
	
	/* All character material such as crafting material, raw materials, and other types. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory System")
	TArray<UItem*> InventoryArray;
	
	/* Default starting items for the characters. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory System")
	TArray<UItem*> StartingItems;

	// Return Over World HUD.
	AOverworldHUD* GetPlayerHUD();
private:
	/* What is the current selected item in the inventory slot? */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory System", meta=(AllowPrivateAccess = "true"))
	UInventorySlot* SelectedSlot;

	// Inventory Capacity per ItemType
	TMap<EItemType, int32> InventoryCapacity;
	
	// Keeps track of the total amount of inventory slot per enum.
	TMap<EItemType, int32> TotalItems;
	
	/* Check to see if a one of the inventory is cur/rently full. */ 
	void CheckIfInventoryIsFull();
	
	/* Spawn point of the dropped items from the actor. */ 
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SpawnPoint;

	/* Blueprint for the item actor. */ 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem_DefaultActor> DefaultActor;

	/* Reactivate collision for item that was dropped. */
	UFUNCTION()
	static void ActivateCollision(AItem_DefaultActor* ItemActor);

	// Check to see if the inventory is for play or chest.
	UPROPERTY(EditDefaultsOnly)
	bool bIsPlayerInventory;

	UPROPERTY()
	AOverworldHUD* PlayerHUD;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};