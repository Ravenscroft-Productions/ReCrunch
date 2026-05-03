// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/InventoryItem.h"
#include "InventoryWidget.generated.h"

class UInventoryContextMenuWidget;
class UInventoryItemWidget;
class UInventoryComponent;
class UWrapBox;
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnFocusChanging(const FWeakWidgetPath& PreviousFocusPath, const FWidgetPath& NewWidgetPath, const FFocusEvent& InFocusEvent) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventoryContextMenuWidget> ContextMenuWidgetClass;
	
	UPROPERTY()
	UInventoryContextMenuWidget* ContextMenuWidget;
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* ItemList;
	
	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	TSubclassOf<UInventoryItemWidget> ItemWidgetClass;
	
	UPROPERTY()
	UInventoryComponent* InventoryComponent;
	
	TArray<UInventoryItemWidget*> ItemWidgets;
	TMap<FInventoryItemHandle, UInventoryItemWidget*> PopulatedItemEntryWidgets;
	FInventoryItemHandle CurrentFocusedItemHandle;
	
	void ItemAdded(const UInventoryItem* InventoryItem);
	void ItemStackCountChanged(const FInventoryItemHandle& Handle, int NewCount);
	UInventoryItemWidget* GetNextAvailableSlot() const;
	void HandleItemDragDrop(UInventoryItemWidget* DestinationWidget, UInventoryItemWidget* SourceWidget);
	void ItemRemoved(const FInventoryItemHandle& ItemHandle);
	void SpawnContextMenu();
	void SetContextMenuVisible(bool bContextMenuVisible);
	void ToggleContextMenu(const FInventoryItemHandle& ItemHandle);
	void ClearContextMenu();
	
	UFUNCTION()
	void SellFocusedItem();
	
	UFUNCTION()
	void UseFocusedItem();
};
