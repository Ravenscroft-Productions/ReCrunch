// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/GameplayWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/CAttributeSet.h"
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
}
