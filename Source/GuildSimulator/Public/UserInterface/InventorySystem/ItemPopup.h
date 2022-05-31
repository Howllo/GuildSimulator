// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPopup.generated.h"

class UButton;
class UTextBlock;
class AOverworldPlayerCharacter;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UItemPopup : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* ItemUse;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* ItemDrop;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* ItemCancel;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* SlotOne;

	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UButton* SlotTwo;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* UseText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* SlotOneText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* SlotTwoText;
	
	UFUNCTION(BlueprintCallable)
	void ButtonCalledUse();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledDrop();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledCancel();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledSlotOne();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledSlotTwo();
private:
	UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	const AOverworldPlayerCharacter* PlayerCharacter; 
};
