// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "UObject/Object.h"
#include "GameplayEffectTypes.h"
#include "InventoryItem.generated.h"

class UGameplayAbility;
class UAbilitySystemComponent;
class UPA_ShopItem;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAbilityCanCastUpdatedDelegate, bool /*bCanCast*/)

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
	FOnAbilityCanCastUpdatedDelegate OnAbilityCanCastUpdated;
	
	UInventoryItem();
	bool IsValid() const;
	void InitItem(const FInventoryItemHandle& NewHandle, const UPA_ShopItem* NewShopItem, UAbilitySystemComponent* AbilitySystemComponent);
	const UPA_ShopItem* GetShopItem() const { return ShopItem; }
	FInventoryItemHandle GetHandle() const { return Handle; }
	bool TryActivateGrantedAbility();
	void ApplyConsumeEffect();
	void RemoveGASModifications();
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
	bool IsGrantingAbility(TSubclassOf<UGameplayAbility> AbilityClass) const;
	bool IsGrantingAnyAbility() const;
	float GetAbilityCooldownTimeRemaining() const;
	float GetAbilityCooldownDuration() const;
	float GetAbilityManaCost() const;
	bool CanCastAbility() const;
	FGameplayAbilitySpecHandle GetGrantedAbilitySpecHandle() const { return GrantedAbilitySpecHandle; }
	void SetGrantedAbilitySpecHandle(FGameplayAbilitySpecHandle SpecHandle) { GrantedAbilitySpecHandle = SpecHandle; }
	
private:
	void ApplyGASModifications();
	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
	
	UPROPERTY()
	const UPA_ShopItem* ShopItem;
	
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
	FInventoryItemHandle Handle;
	FActiveGameplayEffectHandle AppliedEquippedEffectHandle;
	FGameplayAbilitySpecHandle GrantedAbilitySpecHandle;
	int StackCount;
	int Slot;
};
