// Copyright (c) Astral Games. All right reserved.


#include "GameMisc/Item/Item.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/EquipmentSystem.h"
#include "GameMisc/SingleClassCharStats.h"
#include "GameMisc/GuildSimEnums.h"
#include "GameMisc/Item/ConsumableScript.h"
#include "Kismet/GameplayStatics.h"

UItem::UItem()
{
	//Create the CharStats object.
	CharStats = CreateDefaultSubobject<USingleClassCharStats>(TEXT("CharStats"));

	//Create a CharConsumable Object
	ConsumableScript = CreateDefaultSubobject<UConsumableScript>(TEXT("Consumable"));
	
	Quantity = 1;
	TotalQuantityPerStack = 1;
}

void UItem::OnUse()
{
	const auto PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
	if(CharStats)
	{
		if(CharStats->ArmorEnum != EAT_Ring || CharStats->ArmorEnum != EAT_Trinket){
			if(ItemType == IType_Armor || ItemType == IType_Weapon)
			{
				switch (CharStats->HandStyle)
				{
				case EHT_One:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerWeapon(this);
					break;
				case EHT_Two:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerWeapon(this);
					PlayerCharacter->GetPlayerEquipment()->SetPlayerOffHand(nullptr);
					break;
				case EHT_Off:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerOffHand(this);
					break;
				default:
					break;
				}
			}

			if(ItemType == IType_Armor)
			{
				switch (CharStats->ArmorEnum)
				{
				case EAT_Helm:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerHelm(this);
					break;
				case EAT_Chest:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerChest(this);
					break;
				case EAT_Hand:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerHands(this);
					break;
				case EAT_Legs:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerLeggings(this);
					break;
				case EAT_Feet:
					PlayerCharacter->GetPlayerEquipment()->SetPlayerFeet(this);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			//TODO: Add On use for Trinket and ring of being able to select which place to place it. 
		}
	}
	
	if(ConsumableScript)
	{
	}
}

#if WITH_EDITOR // Limits
void UItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	//Enforcing limits.
	Quantity = FMath::Clamp(Quantity, 0, TotalQuantityPerStack);
	
	if(bIsUnique)
	{
		TotalQuantityPerStack = 1;
		Quantity = 1;
	}

	if(!bIsStackable)
	{
		TotalQuantityPerStack = 1;
		Quantity = 1;
	}
}
#endif