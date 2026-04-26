// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/InventoryItemDragAndDropOp.h"
#include "Widgets/InventoryItemWidget.h"

void UInventoryItemDragAndDropOp::SetDraggedItem(UInventoryItemWidget* DraggedItem)
{
	Payload = DraggedItem;
	if (DragVisualClass)
	{
		UItemWidget* DragItemWidget = CreateWidget<UItemWidget>(GetWorld(), DragVisualClass);
		if (DragItemWidget)
		{
			DragItemWidget->SetIcon(DraggedItem->GetIconTexture());
			DefaultDragVisual = DragItemWidget;
		}
	}
}
