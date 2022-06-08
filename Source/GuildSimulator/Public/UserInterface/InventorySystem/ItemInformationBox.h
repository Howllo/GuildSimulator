// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInformationBox.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UVerticalBox;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UItemInformationBox : public UUserWidget
{
	GENERATED_BODY()
public:
	//Called by Blueprint
	UFUNCTION(BlueprintCallable)
	void OnStatsClick();

	//Called by Blueprint
	UFUNCTION(BlueprintCallable)
	void OnItemInfoClick();

	/**
	 * @brief Set all text block elements to collapsed.
	 */
	void SetAllCollapse() const;
	
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundRarity;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta=(BindWidget))
	UButton* StatsInformation;

	UPROPERTY(meta=(BindWidget))
	UButton* ItemInformation;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox; 
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ButtonHorizontalBox;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* IconScrollBarBox;
};
