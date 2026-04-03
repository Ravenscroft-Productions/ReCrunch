// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PA_ShopItem.generated.h"

class UPA_ShopItem;
class UGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FItemCollection
{
	GENERATED_BODY()
public:
	FItemCollection();
	FItemCollection(const TArray<const UPA_ShopItem*>& InItems);
	void AddItem(const UPA_ShopItem* NewItem, bool bAddUnique = false);
	bool Contains(const UPA_ShopItem* Item) const;
	const TArray<const UPA_ShopItem*>& GetItems() const;
	
private:
	TArray<const UPA_ShopItem*> Items;
};
/**
 * 
 */
UCLASS()
class CRUNCH_API UPA_ShopItem : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
	static FPrimaryAssetType GetShopItemAssetType();
	UTexture2D* GetIcon() const;
	FText GetItemName() const { return ItemName; }
	FText GetItemDescription() const { return ItemDescription; }
	float GetPrice() const { return Price; }
	float GetSellPrice() const { return Price / 2.0f; }
	TSubclassOf<UGameplayEffect> GetEquippedEffect() const { return EquippedEffect; }
	TSubclassOf<UGameplayEffect> GetConsumeEffect() const { return ConsumeEffect; }
	TSubclassOf<UGameplayAbility> GetGrantedAbility() const { return GrantedAbility; }
	bool GetIsStackable() const { return bIsStackable; }
	bool GetIsConsumable() const { return bIsConsumable; }
	int GetMaxStackCount() const { return MaxStackCount; }
	const TArray<TSoftObjectPtr<UPA_ShopItem>>& GetIngredients() const { return IngredientItems; }
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	float Price;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	FText ItemName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	FText ItemDescription;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	bool bIsConsumable;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	TSubclassOf<UGameplayEffect> EquippedEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	TSubclassOf<UGameplayEffect> ConsumeEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	TSubclassOf<UGameplayAbility> GrantedAbility;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	bool bIsStackable = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	int MaxStackCount = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shop Item")
	TArray<TSoftObjectPtr<UPA_ShopItem>> IngredientItems;
};
