// Copyright (c) Astral Games. All right reserved.

#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "GameMisc/Item/Item.h"
#include "GameMisc/Item/Item_DefaultActor.h"
#include "GameMisc/GuildSimEnums.h"
#include "GameMisc/SingleClassCharStats.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"
#include "UserInterface/OverworldHUD.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	static ConstructorHelpers::FClassFinder<AItem_DefaultActor> ItemActor(TEXT("/Game/Blueprints/Items/BP_ItemActor"));
	if(ItemActor.Succeeded())
	{
		DefaultActor = ItemActor.Class;
	}
}

void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
	PlayerHUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD());

	// Set Inventory
	InventoryCapacity.Add(IType_Material, 5);
	InventoryCapacity.Add(IType_Consumable, 5);
	InventoryCapacity.Add(IType_Armor, 5);
	InventoryCapacity.Add(IType_Weapon, 5);
	InventoryCapacity.Add(IType_Outfit, 5);
	InventoryCapacity.Add(IType_Crafted, 5);

	// Set Maps
	TotalItems.Add(IType_Material, 0);
	TotalItems.Add(IType_Consumable, 0);
	TotalItems.Add(IType_Armor, 0);
	TotalItems.Add(IType_Weapon, 0);
	TotalItems.Add(IType_Outfit, 0);
	TotalItems.Add(IType_Crafted, 0);
}

bool UInventorySystem::AddItem(UItem* Item)
{
	if(!Item || Item->ItemType == IType_NONE) { return false; }

	bool bLeftOver = false;
	
	if(InventoryArray.Num() != 0 || Item->Quantity != Item->TotalQuantityPerStack)
	{
		for(int32 i = 0; i < InventoryArray.Num(); i++)
		{
			if(InventoryArray[i] != nullptr)
			{
				if(InventoryArray[i]->ItemID == Item->ItemID && InventoryArray[i]->Quantity < InventoryArray[i]->TotalQuantityPerStack)
				{
					if(InventoryArray[i]->Quantity + Item->Quantity <= InventoryArray[i]->TotalQuantityPerStack)
					{
						InventoryArray[i]->Quantity += Item->Quantity;
						Item->Quantity = 0;
						UpdateInventory(Item->ItemType);
						return true;
					}
				
					if(InventoryArray[i]->Quantity + Item->Quantity > InventoryArray[i]->TotalQuantityPerStack)
					{
						const int32 Difference = InventoryArray[i]->TotalQuantityPerStack - InventoryArray[i]->Quantity;
						InventoryArray[i]->Quantity += Difference;
						Item->Quantity -= Difference;
						UpdateInventory(Item->ItemType);
						bLeftOver = true;
					}
				}
			}
		}
	}
	
	if(Item->Quantity > 0 && !bLeftOver && *TotalItems.Find(Item->ItemType) != *InventoryCapacity.Find(Item->ItemType)
		|| Item->Quantity > 0 && bLeftOver && *TotalItems.Find(Item->ItemType) != *InventoryCapacity.Find(Item->ItemType))
	{
		InventoryArray.Add(Item);
		UpdateInventory(Item->ItemType);
		return true;
	}
	
	// If there are left over drop it.
	if(bLeftOver)
	{
		DropItem(Item, Item->Quantity);
	}
	
	return false;
}

bool UInventorySystem::RemoveItem(const UItem* Item)
{
	for(int32 i = 0; i < InventoryArray.Num(); i++)
	{
		if(InventoryArray[i]->ItemID == Item->ItemID && InventoryArray[i]->Quantity == Item->Quantity)
		{
			InventoryArray.RemoveAt(i);
			UpdateInventory(Item->ItemType);
			CheckIfInventoryIsFull();
			return true;
		}
	}
	return false;
}


void UInventorySystem::DropItem(UItem* Item, const int32 Amount)
{
	if(!Item && !GetWorld()) return;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	const AOverworldPlayerCharacter* PlayerChar = Cast<AOverworldPlayerCharacter>(GetOwner());
	const FVector Loc = PlayerChar->GetSpawnPoint()->GetComponentLocation();
	const FRotator Rot = FRotator(PlayerChar->GetSpawnPoint()->GetComponentRotation().Pitch,
						     PlayerChar->GetSpawnPoint()->GetComponentRotation().Yaw + 110,
								  PlayerChar->GetSpawnPoint()->GetComponentRotation().Roll);

	// Create Actor Item.
	AItem_DefaultActor* ItemActor =  GetWorld()->SpawnActor<AItem_DefaultActor>(DefaultActor, Loc, Rot);
	ItemActor->GetSphereCollider()->SetSphereRadius(0.1f);
	
	//Launch drop object.
	ItemActor->GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ItemActor->GetMesh()->SetSimulatePhysics(true);
	ItemActor->GetMesh()->AddImpulse(ItemActor->GetMesh()->GetForwardVector() * 3000.f);

	//Create a Item class duplicate.
	ItemActor->Item = DuplicateObject(Item, nullptr);

	// Check the Quantity
	if(Item->Quantity == Amount)
	{
		ItemActor->Item = Item;
		RemoveItem(Item);
	}
	else if(Item->Quantity != Amount)
	{
		Item->Quantity -= Amount;
		ItemActor->Item->Quantity = Amount;
		UpdateInventory(Item->ItemType);
	}

	// Set timer for GetSphereCollider to be activated.
	TimerDelegate.BindUFunction(this, FName("ActivateCollision"), ItemActor);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 0.5f, false);
}

void UInventorySystem::UpdateInventory(const ItemType Type)
{
	if(Type == IType_NONE) return;
	
	if(bIsPlayerInventory)
	{
		AOverworldHUD* OverworldHUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(this->GetOwner(), 0)->GetHUD());
		OverworldHUD->GetOptionMenuWidget()->UpdateInventorySlots(InventoryArray, Type);
	} else
	{
		//TODO: Create a chest system.
	}
	CheckIfInventoryIsFull();
}

void UInventorySystem::CheckIfInventoryIsFull()
{
	int Mat = 0, Con = 0, Arm = 0, Wep = 0, Out = 0, Craft = 0;
	
	// Reset all items to zero.
	TotalItems[IType_Material] = Mat;
	TotalItems[IType_Consumable] = Con;
	TotalItems[IType_Armor] = Arm;
	TotalItems[IType_Weapon] =  Wep;
	TotalItems[IType_Outfit] = Out;
	TotalItems[IType_Crafted] = Craft;
	
	if(InventoryArray.Num() > 0)
	{
		for(int32 i = 0; i < InventoryArray.Num(); i++)
		{
			switch (InventoryArray[i]->ItemType)
			{
			case IType_Material:
				TotalItems[IType_Material] = Mat++;
				break;
			case IType_Consumable:
				TotalItems[IType_Consumable] = Con++;
				break;
			case IType_Armor:
				TotalItems[IType_Armor] = Arm++;
				break;
			case IType_Weapon:
				TotalItems[IType_Weapon] =  Wep++;
				break;
			case IType_Outfit:
				TotalItems[IType_Outfit] = Out++;
				break;
			case IType_Crafted:
				TotalItems[IType_Crafted] = Craft++;
				break;
			default:
				break;
			}
		}
	}
}

void UInventorySystem::ActivateCollision(AItem_DefaultActor* ItemActor)
{
	ItemActor->GetMesh()->SetSimulatePhysics(false);
	ItemActor->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ItemActor->GetSphereCollider()->SetSphereRadius(37.2f);
}
	
void UInventorySystem::SetBoolPlayerInventory(bool SetPlayerB)
{
	bIsPlayerInventory = SetPlayerB;
}

void UInventorySystem::SetCapacity(const ItemType Type, const int32 Capacity)
{
	InventoryCapacity[Type] = Capacity;
}

TMap<ItemType, int32>& UInventorySystem::GetCapacity() 
{
	return InventoryCapacity;
}

UInventorySlot* UInventorySystem::GetSelectedSlot() const
{
	return SelectedSlot;
}

void UInventorySystem::SetSelectedSlot(UInventorySlot* Slot)
{
	SelectedSlot = Slot;
}

AOverworldHUD* UInventorySystem::GetPlayerHUD()
{
	return PlayerHUD;
}