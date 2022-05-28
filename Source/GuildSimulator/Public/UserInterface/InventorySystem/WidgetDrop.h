// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDrop.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UWidgetDrop : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidgetDrop(const FObjectInitializer& ObjectInitializer);

	// For the use of UserNumberInput
	UFUNCTION(BlueprintCallable)
	void UserNumberFunction();
	
	// For the use of Confirm Button.
	UFUNCTION(BlueprintCallable)
	void ConfirmButtonFunction();

	// For the use of Minus Button.
	UFUNCTION(BlueprintCallable)
	void MinusButtonFunction();

	// For the use of Plus Button.
	UFUNCTION(BlueprintCallable)
	void PlusButtonFunction();

	// For the use of All Button.
	UFUNCTION(BlueprintCallable)
	void AllButtonFunction();
private:
	UPROPERTY(meta=(BindWidget))
	UEditableTextBox* UserNumberInput;

	UPROPERTY(meta=(BindWidget))
	UButton* ConfirmButton;

	UPROPERTY(meta=(BindWidget))
	UButton* AllQuantityButton;

	UPROPERTY(meta=(BindWidget))
	UButton* MinusButton;

	UPROPERTY(meta=(BindWidget))
	UButton* PlusButton;
};
