// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/ItemTooltip.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/PA_ShopItem.h"

void UItemTooltip::SetItem(const UPA_ShopItem* Item)
{
	ItemTitleText->SetText(Item->GetItemName());
	ItemDescriptionText->SetText(Item->GetItemDescription());
	ItemPriceText->SetText(FText::AsNumber((int)Item->GetPrice()));
	IconImage->SetBrushFromTexture(Item->GetIcon());
}

void UItemTooltip::SetPrice(float NewPrice)
{
	ItemPriceText->SetText(FText::AsNumber((int)NewPrice));
}
