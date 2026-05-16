// (c) 2025-6 Ravenscroft-Productions


#include "Inventory/InventoryItem.h"

#include "AbilitySystemComponent.h"
#include "GAS/CAbilitySystemStatics.h"
#include "Inventory/PA_ShopItem.h"

FInventoryItemHandle::FInventoryItemHandle()
	: HandleId{GetInvalidId()}
{	
}

FInventoryItemHandle FInventoryItemHandle::InvalidHandle()
{
	static FInventoryItemHandle InvalidHandle = FInventoryItemHandle();
	return InvalidHandle;
}

FInventoryItemHandle::FInventoryItemHandle(uint32 Id)
	: HandleId{Id}
{
}

FInventoryItemHandle FInventoryItemHandle::CreateHandle()
{
	return FInventoryItemHandle(GenerateNextId());
}

bool FInventoryItemHandle::IsValid() const
{
	return HandleId != GetInvalidId();
}

uint32 FInventoryItemHandle::GenerateNextId()
{
	static uint32 StaticId = 1;
	return StaticId++;
}

uint32 FInventoryItemHandle::GetInvalidId()
{
	return 0;
}

bool operator==(const FInventoryItemHandle& Lhs, const FInventoryItemHandle& Rhs)
{
	return Lhs.GetHandleId() == Rhs.GetHandleId();
}

uint32 GetTypeHash(const FInventoryItemHandle& Key)
{
	return Key.GetHandleId();
}

UInventoryItem::UInventoryItem()
	:StackCount{1}
{	
}

bool UInventoryItem::IsValid() const
{
	return ShopItem != nullptr;
}

void UInventoryItem::InitItem(const FInventoryItemHandle& NewHandle, const UPA_ShopItem* NewShopItem, UAbilitySystemComponent* AbilitySystemComponent)
{
	Handle = NewHandle;
	ShopItem = NewShopItem;
	
	OwnerAbilitySystemComponent = AbilitySystemComponent;
	ApplyGASModifications();
}

bool UInventoryItem::TryActivateGrantedAbility()
{
	if (!GrantedAbilitySpecHandle.IsValid()) return false;
	
	if (OwnerAbilitySystemComponent && OwnerAbilitySystemComponent->TryActivateAbility(GrantedAbilitySpecHandle)) return true;
	
	return false;
}

void UInventoryItem::ApplyConsumeEffect()
{
	if (!ShopItem) return;
	
	TSubclassOf<UGameplayEffect> ConsumeEffect = ShopItem->GetConsumeEffect();
	if (!ConsumeEffect) return;
	
	OwnerAbilitySystemComponent->BP_ApplyGameplayEffectToSelf(ConsumeEffect, 1, OwnerAbilitySystemComponent->MakeEffectContext());
}

void UInventoryItem::RemoveGASModifications()
{
	if (!OwnerAbilitySystemComponent) return;
	
	if (AppliedEquippedEffectHandle.IsValid()) OwnerAbilitySystemComponent->RemoveActiveGameplayEffect(AppliedEquippedEffectHandle);
	
	if (GrantedAbilitySpecHandle.IsValid()) OwnerAbilitySystemComponent->SetRemoveAbilityOnEnd(GrantedAbilitySpecHandle);
}

void UInventoryItem::ApplyGASModifications()
{
	if (!GetShopItem() || !OwnerAbilitySystemComponent) return;
	
	if (!OwnerAbilitySystemComponent->GetOwner() || !OwnerAbilitySystemComponent->GetOwner()->HasAuthority()) return;
	
	TSubclassOf<UGameplayEffect> EquipEffect = GetShopItem()->GetEquippedEffect();
	if (EquipEffect)
	{
		AppliedEquippedEffectHandle = OwnerAbilitySystemComponent->BP_ApplyGameplayEffectToSelf(EquipEffect, 1, OwnerAbilitySystemComponent->MakeEffectContext());
	}
	
	TSubclassOf<UGameplayAbility> GrantedAbility = GetShopItem()->GetGrantedAbility();
	if (GrantedAbility)
	{
		GrantedAbilitySpecHandle = OwnerAbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(GrantedAbility));
	}
}

void UInventoryItem::SetSlot(int NewSlot)
{
	Slot = NewSlot;
}

bool UInventoryItem::IsStackFull() const
{
	return StackCount >= GetShopItem()->GetMaxStackCount();
}

bool UInventoryItem::IsForItem(const UPA_ShopItem* Item) const
{
	if (!Item) return false;
	
	return GetShopItem() == Item;
}

bool UInventoryItem::AddStackCount()
{
	if (IsStackFull()) return false;
	
	++StackCount;
	return true;
}

bool UInventoryItem::ReduceStackCount()
{
	--StackCount;
	if (StackCount <= 0)
	{
		return false;
	}
	
	return true;
}

bool UInventoryItem::SetStackCount(int NewStackCount)
{
	if (NewStackCount >= 0 && NewStackCount <= GetShopItem()->GetMaxStackCount())
	{
		StackCount = NewStackCount;
		return true;
	}
	
	return false;
}

bool UInventoryItem::IsGrantingAbility(TSubclassOf<UGameplayAbility> AbilityClass) const
{
	if (!ShopItem) return false;
	
	TSubclassOf<UGameplayAbility> GrantedAbility = ShopItem->GetGrantedAbility();
	return GrantedAbility == AbilityClass;
}

bool UInventoryItem::IsGrantingAnyAbility() const
{
	if (!ShopItem) return false;
	
	return ShopItem->GetGrantedAbility() != nullptr;
}

float UInventoryItem::GetAbilityCooldownTimeRemaining() const
{
	if (!IsGrantingAnyAbility()) return 0.0f;
	
	return UCAbilitySystemStatics::GetCooldownRemainingFor(GetShopItem()->GetGrantedAbilityCDO(), *OwnerAbilitySystemComponent);
}

float UInventoryItem::GetAbilityCooldownDuration() const
{
	if (!IsGrantingAnyAbility()) return 0.0f;
	
	return UCAbilitySystemStatics::GetCooldownDurationFor(GetShopItem()->GetGrantedAbilityCDO(), *OwnerAbilitySystemComponent, 1);
}

float UInventoryItem::GetAbilityManaCost() const
{
	if (!IsGrantingAnyAbility()) return 0.0f;
	
	return UCAbilitySystemStatics::GetManaCostFor(GetShopItem()->GetGrantedAbilityCDO(), *OwnerAbilitySystemComponent, 1);
}
