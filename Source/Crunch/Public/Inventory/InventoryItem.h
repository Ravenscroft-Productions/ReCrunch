// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "InventoryItem.generated.h"

class UAbilitySystemComponent;
class UPA_ShopItem;

USTRUCT()
struct FInventoryItemHandle
{
	GENERATED_BODY()
public:
	FInventoryItemHandle();
	static FInventoryItemHandle InvalidHandle();
	static FInventoryItemHandle CreateHandle();
	bool IsValid() const;
	uint32 GetHandleId() const { return HandleId; }
	
private:
	UPROPERTY()
	uint32 HandleId;

	explicit FInventoryItemHandle(uint32 Id);
	
	static uint32 GenerateNextId();
	static uint32 GetInvalidId();
};

bool operator==(const FInventoryItemHandle& Lhs, const FInventoryItemHandle& Rhs);
uint32 GetTypeHash(const FInventoryItemHandle& Key);

/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItem : public UObject
{
	GENERATED_BODY()
public:
	UInventoryItem();
	bool IsValid() const;
	void InitItem(const FInventoryItemHandle& NewHandle, const UPA_ShopItem* NewShopItem);
	const UPA_ShopItem* GetShopItem() const { return ShopItem; }
	FInventoryItemHandle GetHandle() const { return Handle; }
	void ApplyGASModifications(UAbilitySystemComponent* AbilitySystemComponent);
	FORCEINLINE int GetStackCount() const { return StackCount; }
	void SetSlot(int NewSlot);
	bool IsStackFull() const;
	bool IsForItem(const UPA_ShopItem* Item) const;
	// returns true if was able to add
	bool AddStackCount();
	// returns true if the stack is not empty after reducing
	bool ReduceStackCount();
	// returns true if was able to set
	bool SetStackCount(int NewStackCount);
	
private:
	UPROPERTY()
	const UPA_ShopItem* ShopItem;
	
	FInventoryItemHandle Handle;
	FActiveGameplayEffectHandle AppliedEquippedEffectHandle;
	FGameplayAbilitySpecHandle GrantedAbilitySpecHandle;
	int StackCount;
	int Slot;
};
