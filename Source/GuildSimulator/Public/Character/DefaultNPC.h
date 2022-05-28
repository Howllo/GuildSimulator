// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultNPC.generated.h"

UCLASS()
class GUILDSIMULATOR_API ADefaultNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Character")
	FText CharacterGender;
	
	UPROPERTY(EditDefaultsOnly, Category="Character")
	int32 CharacterRomance;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TArray<int32> CharacterRomanceLevelRequirements;
	
	UPROPERTY(EditDefaultsOnly, Category="Character")
	int32 CharacterSexual;
	
	UPROPERTY(EditDefaultsOnly, Category="Character")
	TArray<int32> CharacterSexualRequirements;
};
