// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameMisc/GuildSimEnums.h"
#include "DefaultCharacterAI.generated.h"

class ADefaultCharacterAI;
class UInventorySystem;
class USpringArmComponent;
class UCharacterStatistic;
class UInventorySystem;
class UCameraComponent;
class USphereComponent;
class ARaidHUD;

UCLASS()
class GUILDSIMULATOR_API ADefaultCharacterAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADefaultCharacterAI();

protected:
		/* Unit Name */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Information")
	FText Unit_Name;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Information")
	TEnumAsByte<CharacterType> CharacterType;
	
	/* Current target for the character. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat System")
	AActor* TargetActor;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UCapsuleComponent* SelectionCaps;
	
	/*Character stats component.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Combat System")
	UCharacterStatistic* CharacterStatistic;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Inventory")
	UInventorySystem* InventorySystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Information")
	UStaticMeshComponent* CursorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="HUD")
	ARaidHUD* GameHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Physics")
	USphereComponent* SphereComponent;
	
	/**
	 *		- Warrior:			Physical T ank that can only be a tank.
	 *		- Gunslinger:		Physical range DPS.
	 *		- Soulweaver:		Magical ranged healer type.
	 *		- Summoner:			Magical range DPS that deals with summons to fight for them.
	 *		- Ninja:			Physical close combat DPS.
	 *		- Dark Knight:		Physical and magical DPS that can also be a DPS.
	 *		- Ranger:			Physical and magical DPS.
	 *		- Necromancer:		Magical range DPS.
	 *		- Martial Artist:	Physical close combat.
	 *		- Astromancer:		Magical healers that can deal damage and heal at same time.
	 *		- Drunken Fist:		A physical close combat that can be both a tank and DPS.
	 *		- Mecha:			A physical DPS class that is complete a mecha.
	 *		- Sage:				A magical range healer.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterClass> CharacterClass;

	/**
	 *		- Tank:			Passive: Tanks have automatically increased health, defense, and threat generation.
	 *		- Damage:		Passive: Damage have increased movement speed.
	 *		- Healer:		Passive: Healers have increased health and mana regeneration.
	 */
	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<ClassSpecialization> ClassRole;

	/**
	*		- NONE:				This state is just nothing at all. This bypasses most other states.
	*		- COMBAT:			Anything to do with the state of combat.
	*		- DEAD:				State for character being dead.
	*		- STUNNED:			State for character being stunned, usually used for prevent character to cast spells.
	*		- GROUNDED:			If character is on the ground this is the default state.
	*		- COLD AREA:		This is used for players set by environment. Used for cold areas of the map.
	*		- HOT AREA:			This is used for players set by environment. Used for hot areas of the map.
	*		- CANNOT BE DMG:	If character cannot be damage this will be the state.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CurrentCharacterStates> CharacterStateOne;

	/**
	*		- NONE:				This state is just nothing at all. This bypasses most other states.
	*		- COMBAT:			Anything to do with the state of combat.
	*		- DEAD:				State for character being dead.
	*		- STUNNED:			State for character being stunned, usually used for prevent character to cast spells.
	*		- GROUNDED:			If character is on the ground this is the default state.
	*		- COLD AREA:		This is used for players set by environment. Used for cold areas of the map.
	*		- HOT AREA:			This is used for players set by environment. Used for hot areas of the map.
	*		- CANNOT BE DMG:	If character cannot be damage this will be the state.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CurrentCharacterStates> CharacterStateTwo;
	 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterGeneralTraits> FirstGeneralTrait;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterGeneralTraits> SecondGeneralTrait;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterTankTraits> TankTrait;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterDamageTraits> DamageTrait;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Information")
	TEnumAsByte<CharacterHealerTraits> HealerTrait;

	//Equipment Slots
	
	//Passive Array - Auto scaling - Clamp to 3 skills, technical max 2.
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/* Check if character is dead. */
	bool IsCharacterDead();

	/* Set visibility of the static mesh on. */
	void CharacterSelected() const;

	/* Set the visibility of the static mesh off. */
	void CharacterNotSelected() const;

	void PushCharacterOutTheWay(AActor* Collision);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UPROPERTY()
	UArrowComponent* ArrowLeft;

	UPROPERTY()
	UArrowComponent* ArrowRight;
};
