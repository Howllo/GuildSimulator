// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMisc/GuildSimEnums.h"
#include "RaidPlayerCharacter.generated.h"

class ADefaultCharacterAI;
class UInventorySystem;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GUILDSIMULATOR_API ARaidPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARaidPlayerCharacter();

	TEnumAsByte<CharacterType> CharacterType;
	
	//The selected target.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Raid System")
	ADefaultCharacterAI* CurrentSelectedCharacter;
	
	//Raid Character
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Raid System")
	TArray<ADefaultCharacterAI*> RaidGroup;
	
	//Primarily inventory system that holds all the items that the character has.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Inventory System")
	//UInventorySystem* InventorySystem;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCameraComponent* CameraComp;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
