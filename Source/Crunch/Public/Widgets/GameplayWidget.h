// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "GameplayWidget.generated.h"

class UShopWidget;
class UStatsGauge;
class UAbilityListView;
class UAbilitySystemComponent;
class UValueGauge;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities);
	void ToggleShop();
	
private:
	UPROPERTY(meta = (BindWidget))
	UValueGauge* HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	UValueGauge* ManaBar;
	
	UPROPERTY(meta = (BindWidget))
	UAbilityListView* AbilityListView;
	
	UPROPERTY(meta = (BindWidget))
	UStatsGauge* AttackDamageGauge;
	
	UPROPERTY(meta = (BindWidget))
	UStatsGauge* ArmourGauge;
	
	UPROPERTY(meta = (BindWidget))
	UStatsGauge* MoveSpeedGauge;
	
	UPROPERTY(meta = (BindWidget))
	UStatsGauge* IntelligenceGauge;
	
	UPROPERTY(meta = (BindWidget))
	UStatsGauge* StrengthGauge;
	
	UPROPERTY(meta = (BindWidget))
	UShopWidget* ShopWidget;
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShopPopUpAnimation;
	
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
	
	void PlayShopPopUpAnimation(bool bPlayForward);
	void SetOwningPawnInputEnabled(bool bPawnInputEnabled);
	void SetShowMouseCursor(bool bShowMouseCursor);
	void SetFocusToGameAndUI();
	void SetFocusToGameOnly();
};
