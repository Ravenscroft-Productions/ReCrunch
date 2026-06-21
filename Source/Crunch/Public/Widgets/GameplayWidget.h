// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "GameplayWidget.generated.h"

class UCrosshairWidget;
class UCanvasPanel;
class UWidgetSwitcher;
class UGameplayMenu;
class UMatchStatWidget;
class USkeletalMeshRenderWidget;
class UInventoryWidget;
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
	void ShowGameplayMenu();
	void SetGameplayMenuTitle(const FString& NewTitle);
	
	UFUNCTION()
	void ToggleGameplayMenu();
	
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
	
	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* InventoryWidget;
	
	UPROPERTY(meta = (BindWidget))
	USkeletalMeshRenderWidget* HeadshotWidget;
	
	UPROPERTY(meta = (BindWidget))
	UMatchStatWidget* MatchStatWidget;
	
	UPROPERTY(meta = (BindWidget))
	UGameplayMenu* GameplayMenu;
	
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* MainSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GameplayWidgetRootPanel;
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* GameplayMenuRootPanel;
	
	UPROPERTY(meta = (BindWidget))
	UCrosshairWidget* CrosshairWidget;
	
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
