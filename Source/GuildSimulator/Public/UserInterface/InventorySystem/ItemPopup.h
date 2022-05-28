// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPopup.generated.h"

class UButton;
class UTextBlock;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* UseText;

	UFUNCTION(BlueprintCallable)
	void ButtonCalledUse();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledDrop();

	UFUNCTION(BlueprintCallable)
	void ButtonCalledCancel();
};
