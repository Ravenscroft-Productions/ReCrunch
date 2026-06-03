// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/GameplayWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/WidgetSwitcher.h"
#include "GAS/CAbilitySystemComponent.h"
#include "GAS/CAttributeSet.h"
#include "Widgets/AbilityListView.h"
#include "Widgets/GameplayMenu.h"
#include "Widgets/ShopWidget.h"
#include "Widgets/ValueGauge.h"

void UGameplayWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	
	if (OwnerAbilitySystemComponent)
	{
		HealthBar->SetAndBindToGameplayAttribute(OwnerAbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBindToGameplayAttribute(OwnerAbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());
	}
	
	SetShowMouseCursor(false);
	SetFocusToGameOnly();
	if (GameplayMenu)
	{
		GameplayMenu->GetResumeButtonClickedEventDelegate().AddDynamic(this, &UGameplayWidget::ToggleGameplayMenu);
	}
}

void UGameplayWidget::ConfigureAbilities(const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& Abilities)
{	
	AbilityListView->ConfigureAbilities(Abilities);
}

void UGameplayWidget::ToggleShop()
{
	if (ShopWidget->GetVisibility() == ESlateVisibility::HitTestInvisible)
	{
		ShopWidget->SetVisibility(ESlateVisibility::Visible);
		PlayShopPopUpAnimation(true);
		SetOwningPawnInputEnabled(false);
		SetShowMouseCursor(true);
		SetFocusToGameAndUI();
		ShopWidget->SetFocus();
	}
	else
	{
		ShopWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		PlayShopPopUpAnimation(false);
		SetOwningPawnInputEnabled(true);
		SetShowMouseCursor(false);
		SetFocusToGameOnly();
	}
}

void UGameplayWidget::ToggleGameplayMenu()
{
	if (MainSwitcher->GetActiveWidget() == GameplayMenuRootPanel)
	{
		MainSwitcher->SetActiveWidget(GameplayWidgetRootPanel);
		SetOwningPawnInputEnabled(true);
		SetShowMouseCursor(false);
		SetFocusToGameOnly();
	}
	else
	{
		ShowGameplayMenu();
	}
}

void UGameplayWidget::ShowGameplayMenu()
{
	MainSwitcher->SetActiveWidget(GameplayMenuRootPanel);
	SetOwningPawnInputEnabled(false);
	SetShowMouseCursor(true);
	SetFocusToGameAndUI();
}

void UGameplayWidget::SetGameplayMenuTitle(const FString& NewTitle)
{
	GameplayMenu->SetTitleText(NewTitle);
}

void UGameplayWidget::PlayShopPopUpAnimation(bool bPlayForward)
{
	if (bPlayForward)
	{
		PlayAnimationForward(ShopPopUpAnimation);
	}
	else
	{
		PlayAnimationReverse(ShopPopUpAnimation);
	}
}

void UGameplayWidget::SetOwningPawnInputEnabled(bool bPawnInputEnabled)
{
	if (bPawnInputEnabled)
	{
		GetOwningPlayerPawn()->EnableInput(GetOwningPlayer());
	}
	else
	{
		GetOwningPlayerPawn()->DisableInput(GetOwningPlayer());
	}
}

void UGameplayWidget::SetShowMouseCursor(bool bShowMouseCursor)
{
	GetOwningPlayer()->SetShowMouseCursor(bShowMouseCursor);
}

void UGameplayWidget::SetFocusToGameAndUI()
{
	FInputModeGameAndUI GameAndUIInputMode;
	GameAndUIInputMode.SetHideCursorDuringCapture(false);
	GetOwningPlayer()->SetInputMode(GameAndUIInputMode);
}

void UGameplayWidget::SetFocusToGameOnly()
{
	FInputModeGameOnly GameOnlyInputMode;
	GetOwningPlayer()->SetInputMode(GameOnlyInputMode);
}
