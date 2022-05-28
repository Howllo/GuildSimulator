// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "GameMisc/GuildSimEnums.h"
#include "Kismet/GameplayStatics.h"
#include "OptionMenuWidget.generated.h"

class UButton;
class UScrollBox;
class UItemInformationBox;
class UNoItem;
class UInventorySystem;
class UInventorySlot;
class UWidgetDrop;
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UOptionMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UOptionMenuWidget(const FObjectInitializer& ObjectInitializer);

	/**
	 * @brief Returns material grid panel.
	 * @return Return the material Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetMaterialGridPanel();

	/**
	 * @brief Returns consumable grid panel.
	 * @return Return the consumable Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetConsumableGridPanel();

	/**
	 * @brief Returns armor grid panel.
	 * @return Return the armor Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetArmorGridPanel();

	/**
	 * @brief Returns weapon grid panel.
	 * @return Return the weapon Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetWeaponGridPanel();

	/**
	 * @brief Returns outfit grid panel.
	 * @return Return the outfit Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetOutfitGridPanel();

	/**
	 * @brief Returns crafted grid panel.
	 * @return Return the crafted Uniform Grid Panel. 
	 */
	UFUNCTION(BlueprintCallable)
	UUniformGridPanel* GetCraftedGridPanel();

	// Information box that display all the items information.
	UFUNCTION(BlueprintCallable)
	UItemInformationBox* GetInfoBox();
	
private:
	/* Grid panel for the use of materials. */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* MatInventoryGrid;

	/* Grid panel for the use of consumables */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* ConInventoryGrid;

	/* Grid Panel for the use of armor */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* ArmorInventoryGrid;

	/* Grid panel for the use of weapons */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* WeaponInventoryGrid;

	/* Grid panel for the use of outfits */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* OutfitInventoryGrid;

	/* Grid panel for the use of crafted items */
	UPROPERTY(meta=(BindWidget), BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UUniformGridPanel* CraftedInventoryGrid;
	
	/* BP version of Inventory Slots */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventorySlot> BP_Slots;
	
	/* BP version of no item slot. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UNoItem> BP_NoItemInventory;

	/* Option menu information box that shows up on the right side. */
	UPROPERTY(meta=(BindWidget))
	UItemInformationBox* InformationBox;

	// Button Tab

	/* Button for displaying the material grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* MaterialTab;

	/* Button for displaying the consumable grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* ConsumableTab;

	/* Button for displaying the crafted grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* CraftedTab;
	
	/* Button for displaying the weapon grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* WeaponTab;

	/* Button for displaying the armor grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* ArmorTab;

	/* Button for displaying the outfit grid. */
	UPROPERTY(meta=(BindWidget))
	UButton* OutfitTab;

	/* Scroll box just in case something needs to be edited. */
	UPROPERTY(meta=(BindWidget))
	UScrollBox* ScrollBox;

	/* Use to get the last button to undo the changes that occured. */
	UPROPERTY()
	UButton* LastButton;

	/* Use to get the last panel that was used to collapse the widget. */
	UPROPERTY()
	UUniformGridPanel* LastPanel;

	// BP version of WidgetDrop.
	UPROPERTY()
	TSubclassOf<UWidgetDrop> BP_WidgetDrop;

	//Constructed version of BP.
	UPROPERTY()
	UWidgetDrop* WidgetDrop;
public:
	//Delegates
	
	// OnClick button for the material tab.
	UFUNCTION(BlueprintCallable)
	void OnMaterialTab();

	// OnClick button for the consumable tab.
	UFUNCTION(BlueprintCallable)
	void OnConsumableTab();

	// OnClick button for the armor tab.
	UFUNCTION(BlueprintCallable)
	void OnArmorTab();

	UFUNCTION(BlueprintCallable)
	void OnWeaponTab();
	
	// OnClick button for the OutfitTab.
	UFUNCTION(BlueprintCallable)
	void OnOutfitTab();

	// OnClick button for the Crafted tab.
	UFUNCTION(BlueprintCallable)
	void OnCraftedTab();
	
	//Set Button is default.
	void ButtonSetup(UButton* NewLastButton,  UUniformGridPanel* NewPanel);
	
	/**
	 * @brief Updates the inventory slots based on class. Does not update all inventory at once.
	 * @param Items Array that is based by const reference and based on T.
	 * @param Type ItemType enum.
	 */
	void UpdateInventorySlots(TArray<UItem*>& Items, ItemType Type) const;

	/**
	 * @brief Just returns widget of WidgetDrop.
	 * @return - Created widget of UWidgetDrop.
	 */
	UWidgetDrop* GetWidgetDrop();

	// Popups up the UI Widget to be dropped.
	UFUNCTION(BlueprintCallable)
	void DropAction();
};