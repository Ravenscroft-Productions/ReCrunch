// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemTooltip.generated.h"

class UPA_ShopItem;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UItemTooltip : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetItem(const UPA_ShopItem* Item);
	void SetPrice(float NewPrice);
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* IconImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemTitleText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescriptionText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemPriceText;
};
