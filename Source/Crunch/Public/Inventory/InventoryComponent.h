// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UPA_ShopItem;
class UAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CRUNCH_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();	
	void TryPurchase(const UPA_ShopItem* ItemToPurchase);
	float GetGold() const;
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;

/***************************************************************/
/*                          Server                             */
/***************************************************************/
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Purchase(const UPA_ShopItem* ItemToPurchase);
};
