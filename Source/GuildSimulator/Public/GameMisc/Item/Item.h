// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMisc/GuildSimEnums.h"
#include "Item.generated.h"

class UTexture2D;
class USingleClassCharStats;
class UConsumableScript;

/**
 *		Item system for the entire game. Add on to the item system by creating new scripts.
 */
UCLASS(BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced) //Abstract,
class GUILDSIMULATOR_API UItem : public UObject
{
	 GENERATED_BODY()
public:
	UItem();
	
	/* Used for searching and sorting inventory. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required Information")
	int32 ItemID;
	
	/*Display name for the item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	FText ItemName;

	/*Description Text for the item for the item.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	FText ItemDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required Information")
	FText ItemLocation;

	/* Set static mesh for it be exist in World. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required INformation|Dropped Mesh / Placed Mesh")
	UStaticMesh* WorldMesh;

	// For character changing out outfits. Do not uses static mesh for outfit.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required Information|Character Mesh")
	USkeletalMesh* SkeletalMesh;
	
	/**
	*		- Material:		Raw materials that have not been turned into a final product.
	*		- Consumable:	Food, Potion, and Elixir that increase stats of characters.
	*		- Armor:		Anything that a character can wear. Does not display.
	*		- Weapon:		Anything that a character can wield. Does not display.
	*		- Outfit:		Anything that will display on a character. Full outfit, or weapon.
	*		- Crafted:		Anything that cna be placed in the world.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required Information")
	TEnumAsByte<ItemType> ItemType;

	/**
	*		- One:		Boosted properties by 1x.
	*		- Two:		Boosted properties by 2x.
	*		- Three:	Boosted properties by 3x.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required Information")
	TEnumAsByte<ItemStarCount> StarCount;
	
	/**
	*		- Normal:		Normal is lowest rarity, popups all the time.
	*		- Uncommon:		Uncommon is popup decent amount of times, but not all the time.
	*		- Epic:			Rare items that not common at all.
	*		- Legendary:	The idea of legendary is meant to be around 2% chance to get it.
	*		- Artifact:		One item in all the game.
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required Information")
	TEnumAsByte<GameRarity> ItemRarity;
	
	/* Display icon in inventory system..*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	UTexture2D* ItemIcon;

	/* Icon that displays how many times the item was upgraded. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Not Required")
	UTexture2D* ItemUpgradeIcon;

	/* Element Resistance type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Not Required")
	UTexture2D* ResistanceType;
	
	/* Display rarity background in inventory system..*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	UTexture2D* BackgroundRarity;

	/* Display rarity background in inventory system..*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	UTexture2D* BackgroundRaritySelected;
	
	/* Can an item be stack or not? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required Information")
	bool bIsStackable;
		
	/* Only used for armor. Can there be one then one equiped? */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	bool bIsUnique;

	/* Total amount of items that are allowed per stack before creating a new stack. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required Information", meta=(EditCondition="bIsStackable", ClampMin =1))
	int32 TotalQuantityPerStack;

	/* The total amount of items currently or given in a stack. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required Information", meta=(EditCondition="!bIsUnique", ClampMin=0))
	int32 Quantity;
		
	/* The total amount of per item. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Required Information")
	int32 ItemGoldValue;

	// Create new Scripts

	// Character Stats for Armor and Weapons.
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Scripts (Double Click)")
	USingleClassCharStats* CharStats;

	// Consumable script deals with on use.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Scripts (Double Click)")
	UConsumableScript* ConsumableScript;

	// Use the Item
	void OnUse();
private:
	virtual UWorld* GetWorld() const { return World; }
	UPROPERTY(Transient)
	UWorld* World;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};


