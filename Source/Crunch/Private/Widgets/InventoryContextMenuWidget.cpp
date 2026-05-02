// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/InventoryContextMenuWidget.h"

FOnButtonClickedEvent& UInventoryContextMenuWidget::GetSellButtonClickedEvent() const
{
	return SellButton->OnClicked;
}

FOnButtonClickedEvent& UInventoryContextMenuWidget::GetUseButtonClickedEvent() const
{
	return UseButton->OnClicked;
}
