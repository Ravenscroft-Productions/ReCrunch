// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "Inventory/InventoryItem.h"
#include "InventoryItemWidget.generated.h"

class UInventoryItemWidget;
class UInventoryItemDragAndDropOp;
class UInventoryItem;
class UTextBlock;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnInventoryItemDropped, UInventoryItemWidget* /*Destination Widget*/, UInventoryItemWidget* /*Source Widget*/)
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItemWidget : public UItemWidget
{
	GENERATED_BODY()
public:
	FOnInventoryItemDropped OnInventoryItemDropped;
	
	virtual void NativeConstruct() override;
	void UpdateInventoryItem(const UInventoryItem* Item);
	bool IsEmpty() const;
	void SetSlotNumber(int NewSlotNumber);
	FORCEINLINE int GetSlotNumber() const { return SlotNumber; }
	void EmptySlot();
	void UpdateStackCount();
	UTexture2D* GetIconTexture() const;
	FORCEINLINE const UInventoryItem* GetInventoryItem() const { return InventoryItem; }
	FInventoryItemHandle GetItemHandle() const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	UTexture2D* EmptyTexture;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackCountText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CooldownCountText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CooldownDurationText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ManaCostText;
	
	UPROPERTY()
	const UInventoryItem* InventoryItem;
	
	int SlotNumber;
	
	/***********************************************/
	/*                Drag and Drop                */
	/***********************************************/
private:
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Drag and Drop")
	TSubclassOf<UInventoryItemDragAndDropOp> DragDropOpClass;
};
