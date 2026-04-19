// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/InventoryItemWidget.h"

#include "Components/TextBlock.h"
#include "Inventory/InventoryItem.h"
#include "Inventory/PA_ShopItem.h"
#include "Widgets/ItemTooltip.h"

void UInventoryItemWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	EmptySlot();
}

void UInventoryItemWidget::UpdateInventoryItem(const UInventoryItem* Item)
{
	InventoryItem = Item;
	if (!InventoryItem || !InventoryItem->IsValid() || InventoryItem->GetStackCount() <= 0)
	{
		EmptySlot();
		return;
	}
	
	SetIcon(Item->GetShopItem()->GetIcon());
	UItemTooltip* Tooltip = SetTooltipWidget(InventoryItem->GetShopItem());
	if (Tooltip)
	{
		Tooltip->SetPrice(InventoryItem->GetShopItem()->GetSellPrice());
	}
	
	if (InventoryItem->GetShopItem()->GetIsStackable())
	{
		StackCountText->SetVisibility(ESlateVisibility::Visible);
		UpdateStackCount();
	}
	else
	{
		StackCountText->SetVisibility(ESlateVisibility::Hidden);
	}
}

bool UInventoryItemWidget::IsEmpty() const
{
	return !InventoryItem || !InventoryItem->IsValid();
}

void UInventoryItemWidget::SetSlotNumber(int NewSlotNumber)
{
	SlotNumber = NewSlotNumber;
}

void UInventoryItemWidget::EmptySlot()
{
	InventoryItem = nullptr;
	SetIcon(EmptyTexture);
	SetTooltipWidget(nullptr);
	
	StackCountText->SetVisibility(ESlateVisibility::Hidden);
	ManaCostText->SetVisibility(ESlateVisibility::Hidden);
	CooldownCountText->SetVisibility(ESlateVisibility::Hidden);
	CooldownDurationText->SetVisibility(ESlateVisibility::Hidden);
}

void UInventoryItemWidget::UpdateStackCount()
{
	if (InventoryItem)
	{
		StackCountText->SetText(FText::AsNumber(InventoryItem->GetStackCount()));
	}
}
