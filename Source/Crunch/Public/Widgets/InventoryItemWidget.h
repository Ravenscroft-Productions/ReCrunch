// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "ItemWidget.h"
#include "InventoryItemWidget.generated.h"

class UInventoryItem;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CRUNCH_API UInventoryItemWidget : public UItemWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void UpdateInventoryItem(const UInventoryItem* Item);
	bool IsEmpty() const;
	FORCEINLINE int GetSlotNumber() const { return SlotNumber; }
	void EmptySlot();
	
private:
	void UpdateStackCount();
	
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
};
