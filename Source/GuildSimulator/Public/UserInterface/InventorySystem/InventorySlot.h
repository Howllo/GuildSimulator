// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UImage;
class UTextBlock;
class UButton;
class USizeBox;
class UItem;
class UPopupSelectedBox;
class UItemPopup;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UInventorySlot(const FObjectInitializer& ObjectInitializer);
	
	// Set the 
	UFUNCTION(BlueprintCallable)
	void OnSlotClicked();

	// Set slots widget with proper information.
	UFUNCTION(BlueprintCallable)
	void SetSlot();
	
	//Quantity or Damage Text.
	UPROPERTY(meta=(BindWidget))
	UTextBlock* InformationText;

	UPROPERTY(meta=(BindWidget))
	USizeBox* StarOne;

	UPROPERTY(meta=(BindWidget))
	USizeBox* StarTwo;

	UPROPERTY(meta=(BindWidget))
	USizeBox* StarThree;

	// Show what type of resistance this item has.
	UPROPERTY(meta=(BindWidget))
	UImage* ResistanceType;
	
	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	// Icon to display that the item was upgraded.
	UPROPERTY(meta=(BindWidget))
	UImage* UpgradedIcon;

	UPROPERTY(meta=(BindWidget))
	UButton* ClickButton;
	
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundRarity;
	
	// Class Holders
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UItem* MainItem = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bSelected;

	/**
	 * @brief Returns the popup menu from the inventory slot.
	 * @return UItemPopup - Return the ItemPopup widget.
	 */
	UItemPopup* GetPopup();

	UFUNCTION(BlueprintCallable)
	bool GetIsActive();
private:
	UPROPERTY()
	UItemPopup* PopupInfo;
	
	UPROPERTY()
	TSubclassOf<UItemPopup> BP_ItemPopup;

	// Create the Widget.
	void PopupWidget();

	// Set The Buttons for each slots when clicked.
	void ChangePopupButtons() const;

	UPROPERTY()
	bool bIsActive;
};