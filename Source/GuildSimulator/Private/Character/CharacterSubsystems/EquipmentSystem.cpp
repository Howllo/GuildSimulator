// Copyright (c) Astral Games. All right reserved.


#include "Character/CharacterSubsystems/EquipmentSystem.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "GameMisc/SingleClassCharStats.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UEquipmentSystem::UEquipmentSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// Set the Capacity.
	ConsumableCapacity = 4;
	
	// Set consumable array.
	PlayerConsumables.SetNum(ConsumableCapacity);

	//Set Default Array
	PlayerRing.SetNum(2);
	PlayerTrinket.SetNum(2);
}

int32 UEquipmentSystem::GetConsumableCapacity()
{
	return ConsumableCapacity;
}

void UEquipmentSystem::SetConsumableCapacity(int32 TotalCapacity)
{
	ConsumableCapacity = TotalCapacity;
	PlayerConsumables.SetNum(ConsumableCapacity);
}

UItem* UEquipmentSystem::GetPlayerHelm()
{
	return PlayerHelm;
}

void UEquipmentSystem::SetPlayerHelm(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerHelm());
	PlayerHelm = Item;
}

UItem* UEquipmentSystem::GetPlayerChest()
{
	return PlayerChest;
}

void UEquipmentSystem::SetPlayerChest(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerChest());
	PlayerChest = Item;
}

UItem* UEquipmentSystem::GetPlayerHands()
{
	return PlayerHands;
}

void UEquipmentSystem::SetPlayerHands(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerHands());
	PlayerHands = Item;
}

UItem* UEquipmentSystem::GetPlayerLeggings()
{
	return PlayerLeggings;
}

void UEquipmentSystem::SetPlayerLeggings(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerLeggings());
	PlayerLeggings = Item;
}

UItem* UEquipmentSystem::GetPlayerFeet()
{
	return PlayerFeet;
}

void UEquipmentSystem::SetPlayerFeet(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerFeet());
	PlayerFeet = Item;
}

UItem* UEquipmentSystem::GetPlayerRing(const int32 Slot)
{
	if( Slot == 0 )
	{
		return PlayerRing[Slot - 1];
	}

	if( Slot == 1 )
	{
		return PlayerRing[Slot - 1];
	}
	return nullptr;
}

void UEquipmentSystem::SetPlayerRing(UItem* Item, const int32 Slot)
{
	if( Slot == 1 )
	{
		PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
		RemoveArmor(GetPlayerRing(Slot));
		PlayerRing[Slot - 1] = Item;
	}

	if( Slot == 2 )
	{
		PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
		RemoveArmor(GetPlayerRing(Slot));
		PlayerRing[Slot - 1] = Item;
	}
}

UItem* UEquipmentSystem::GetPlayerTrinket(const int32 Slot)
{
	if( Slot == 1 )
	{
		return PlayerTrinket[Slot - 1];
	}
	
	if( Slot == 2 )
	{
		return PlayerTrinket[Slot - 1];
	}
	return nullptr;
}

void UEquipmentSystem::SetPlayerTrinket(UItem* Item, int32 Slot)
{
	if( Slot == 1 )
	{
		PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
		RemoveArmor(GetPlayerTrinket(Slot));
		PlayerTrinket[Slot - 1] = Item;
	}

	if( Slot == 2 )
	{
		PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
		RemoveArmor(GetPlayerTrinket(Slot));
		PlayerTrinket[Slot - 1] = Item;
	}
}

UItem* UEquipmentSystem::GetPlayerWeapon()
{
	return PlayerWeapon;
}

void UEquipmentSystem::SetPlayerWeapon(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerWeapon());
	PlayerWeapon = Item;
}

UItem* UEquipmentSystem::GetPlayerOffHand()
{
	return PlayerOffHand;
}

void UEquipmentSystem::SetPlayerOffHand(UItem* Item)
{
	PlayerCharacter->GetInventorySystem()->RemoveItem(Item);
	RemoveArmor(GetPlayerOffHand());
	PlayerOffHand = Item;
}

TArray<UItem*>& UEquipmentSystem::GetPlayerConsumables()
{
	return PlayerConsumables;
}

bool UEquipmentSystem::AddPlayerConsumables(UItem* Item)
{
	if(PlayerConsumables.Num() != ConsumableCapacity)
	{
		PlayerConsumables.Add(Item);
		return true;
	}
	return false;
}

bool UEquipmentSystem::RemoveItemFromConsumables(UItem* Item)
{
	for(int32 i = 0; i < PlayerConsumables.Num(); i++)
	{
		if(PlayerConsumables[i] == Item)
		{
			UItem* Holder = PlayerConsumables[i];
			PlayerConsumables.RemoveAt(i);
			PlayerCharacter->GetInventorySystem()->AddItem(Holder);
			return true;
		}
	}
	return false;
}

bool UEquipmentSystem::RemoveArmor(const UItem* Item)
{
	UItem* Holder = nullptr;
	
	if(Item == PlayerHelm)
	{
		Holder = PlayerHelm;
		PlayerHelm = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item == PlayerChest)
	{
		Holder = PlayerChest;
		PlayerChest = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item == PlayerHands)
	{
		Holder = PlayerHands;
		PlayerHands = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item == PlayerLeggings)
	{
		Holder = PlayerLeggings;
		PlayerLeggings = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item == PlayerFeet)
	{
		Holder = PlayerFeet;
		PlayerFeet = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item->CharStats->ArmorEnum == EAT_Ring)
	{
		for(int32 i = 0; i < PlayerRing.Num(); i++)
		{
			if(PlayerRing[i] == Item)
			{
				Holder = PlayerRing[i];
				PlayerRing[i] = nullptr;
				PlayerCharacter->GetInventorySystem()->AddItem(Holder);
				return true;
			}
		}
	}

	if(Item->CharStats->ArmorEnum == EAT_Trinket)
	{
		for(int32 i = 0; i < PlayerTrinket.Num(); i++)
		{
			if(PlayerTrinket[i] == Item)
			{
				Holder = PlayerTrinket[i];
				PlayerTrinket[i] = nullptr;
				PlayerCharacter->GetInventorySystem()->AddItem(Holder);
				return true;
			}
		}
	}
	
	if(Item == PlayerWeapon)
	{
		Holder = PlayerWeapon;
		PlayerWeapon = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}

	if(Item == PlayerOffHand)
	{
		Holder = PlayerOffHand;
		PlayerOffHand = nullptr;
		PlayerCharacter->GetInventorySystem()->AddItem(Holder);
		return true;
	}
	return false;
}


// Called when the game starts
void UEquipmentSystem::BeginPlay()
{
	Super::BeginPlay();

	// Get Player Character.
	PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
