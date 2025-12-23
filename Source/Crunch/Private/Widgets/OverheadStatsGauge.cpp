// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/OverheadStatsGauge.h"

#include "GAS/CAttributeSet.h"
#include "Widgets/ValueGauge.h"

void UOverheadStatsGauge::ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent)
{
	if (AbilitySystemComponent)
	{
		HealthBar->SetAndBindToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetHealthAttribute(), UCAttributeSet::GetMaxHealthAttribute());
		ManaBar->SetAndBindToGameplayAttribute(AbilitySystemComponent, UCAttributeSet::GetManaAttribute(), UCAttributeSet::GetMaxManaAttribute());
	}
}
