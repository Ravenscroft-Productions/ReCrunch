// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UPA_ShopItem;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAddedDelegate, const UInventoryItem* /*NewItem*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemStackCountChangedDelegate, const FInventoryItemHandle&, int /*NewCount*/);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();	
	FOnItemAddedDelegate OnItemAdded;
	FOnItemStackCountChangedDelegate OnItemStackCountChanged;
	void TryPurchase(const UPA_ShopItem* ItemToPurchase);
	float GetGold() const;
	FORCEINLINE int GetCapacity() const { return Capacity; }
	void ItemSlotChanged(const FInventoryItemHandle& Handle, int NewSlotNumber);
	UInventoryItem* GetInventoryItemByHandle(const FInventoryItemHandle& Handle) const;
	bool IsFullFor(const UPA_ShopItem* Item) const;
	bool IsAllSlotOccupied() const;
	UInventoryItem* GetAvailableStackForItem(const UPA_ShopItem* Item) const;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Capacity = 6;
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;

	UPROPERTY()
	TMap<FInventoryItemHandle, UInventoryItem*> InventoryMap;
		
/***************************************************************/
/*                          Server                             */
/***************************************************************/
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Purchase(const UPA_ShopItem* ItemToPurchase);
	void GrantItem(const UPA_ShopItem* NewItem);
	
/***************************************************************/
/*                          Client                             */
/***************************************************************/
private:
	UFUNCTION(Client, Reliable)
	void Client_ItemAdded(FInventoryItemHandle AssignedHandle, const UPA_ShopItem* Item);
	
	UFUNCTION(Client, Reliable)
	void Client_ItemStackChanged(FInventoryItemHandle Handle, int NewCount);
};
