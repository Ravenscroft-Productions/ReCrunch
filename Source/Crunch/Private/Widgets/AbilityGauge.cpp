// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/AbilityGauge.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GAS/CAbilitySystemStatics.h"
#include "GAS/CAttributeSet.h"
#include "GAS/CHeroAttributeSet.h"

void UAbilityGauge::NativeConstruct()
{
	Super::NativeConstruct();
	CooldownCounterText->SetVisibility(ESlateVisibility::Hidden);
	UAbilitySystemComponent* OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (OwnerASC)
	{
		OwnerASC->AbilityCommittedCallbacks.AddUObject(this, &UAbilityGauge::AbilityCommitted);
		OwnerASC->AbilitySpecDirtiedCallbacks.AddUObject(this, &UAbilityGauge::AbilitySpecUpdated);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCHeroAttributeSet::GetUpgradePointAttribute()).AddUObject(this, &UAbilityGauge::UpgradePointUpdated);
		OwnerASC->GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetManaAttribute()).AddUObject(this, &UAbilityGauge::ManaUpdated);
		bool bFound = false;
		float UpgradePoint = OwnerASC->GetGameplayAttributeValue(UCHeroAttributeSet::GetUpgradePointAttribute(), bFound);
		if (bFound)
		{
			FOnAttributeChangeData ChangeData;
			ChangeData.NewValue = UpgradePoint;
			UpgradePointUpdated(ChangeData);
		}
	}
	
	OwnerAbilitySystemComponent = OwnerASC;
	WholeNumberFormattingOptions.MaximumFractionalDigits = 0;
	TwoDigitNumberFormattingOptions.MaximumFractionalDigits = 2;
}

void UAbilityGauge::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	AbilityCDO = Cast<UGameplayAbility>(ListItemObject);
	
	float CooldownDuration = UCAbilitySystemStatics::GetStaticCooldownDurationForAbility(AbilityCDO);
	float Cost = UCAbilitySystemStatics::GetStaticCostForAbility(AbilityCDO);
	
	CooldownDurationText->SetText(FText::AsNumber(CooldownDuration));
	CostText->SetText(FText::AsNumber(Cost));
	LevelGauge->GetDynamicMaterial()->SetScalarParameterValue(AbilityLevelParamName, 0.0f);
}

void UAbilityGauge::ConfigureWithWidgetData(const FAbilityWidgetData* WidgetData)
{
	if (Icon && WidgetData)
	{
		Icon->GetDynamicMaterial()->SetTextureParameterValue(IconMaterialParamName, WidgetData->Icon.LoadSynchronous());
	}
}

void UAbilityGauge::AbilityCommitted(UGameplayAbility* Ability)
{
	if (Ability->GetClass()->GetDefaultObject() == AbilityCDO)
	{
		float CooldownTimeRemaining = 0.f;
		float CooldownDuration = 0.f;
		
		Ability->GetCooldownTimeRemainingAndDuration(Ability->GetCurrentAbilitySpecHandle(), Ability->GetCurrentActorInfo(), CooldownTimeRemaining, CooldownDuration);
		
		StartCooldown(CooldownTimeRemaining, CooldownDuration);
	}
}

void UAbilityGauge::StartCooldown(float CooldownTimeRemaining, float CooldownDuration)
{
	CachedCooldownDuration = CooldownDuration;
	CooldownDurationText->SetText(FText::AsNumber(CooldownDuration));
	CachedCooldownTimeRemaining = CooldownTimeRemaining;
	
	CooldownCounterText->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAbilityGauge::CooldownFinished, CooldownTimeRemaining);
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerUpdateHandle, this, &UAbilityGauge::UpdateCooldown, CooldownUpdateInterval, true, 0.0f);
}

void UAbilityGauge::CooldownFinished()
{
	CachedCooldownDuration = CachedCooldownTimeRemaining = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(CooldownTimerUpdateHandle);
	CooldownCounterText->SetVisibility(ESlateVisibility::Hidden);
	Icon->GetDynamicMaterial()->SetScalarParameterValue(CooldownPercentParamName, 1.0f);
}

void UAbilityGauge::UpdateCooldown()
{
	CachedCooldownTimeRemaining -= CooldownUpdateInterval;	
	FNumberFormattingOptions* FormattingOptions = CachedCooldownTimeRemaining > 1.0f ? &WholeNumberFormattingOptions : &TwoDigitNumberFormattingOptions;	
	CooldownCounterText->SetText(FText::AsNumber(CachedCooldownTimeRemaining, FormattingOptions));
	
	Icon->GetDynamicMaterial()->SetScalarParameterValue(CooldownPercentParamName, 1.0f - (CachedCooldownTimeRemaining / CachedCooldownDuration));
}

const FGameplayAbilitySpec* UAbilityGauge::GetAbilitySpec()
{
	if (!CachedAbilitySpec)
	{
		if (AbilityCDO && OwnerAbilitySystemComponent)
		{
			CachedAbilitySpec = OwnerAbilitySystemComponent->FindAbilitySpecFromClass(AbilityCDO->GetClass());
		}
	}
	
	return CachedAbilitySpec;
}

void UAbilityGauge::AbilitySpecUpdated(const FGameplayAbilitySpec& AbilitySpec)
{
	if (AbilitySpec.Ability != AbilityCDO) return;
	
	bIsAbilityLearned = AbilitySpec.Level > 0;
	LevelGauge->GetDynamicMaterial()->SetScalarParameterValue(AbilityLevelParamName, AbilitySpec.Level);
	UpdateCanCast();
	
	float NewCooldownDuration = UCAbilitySystemStatics::GetCooldownDurationFor(AbilitySpec.Ability, *OwnerAbilitySystemComponent, AbilitySpec.Level);
	float NewCost = UCAbilitySystemStatics::GetManaCostFor(AbilitySpec.Ability, *OwnerAbilitySystemComponent, AbilitySpec.Level);
	CooldownDurationText->SetText(FText::AsNumber(NewCooldownDuration));
	CostText->SetText(FText::AsNumber(NewCost));
}

void UAbilityGauge::UpdateCanCast()
{
	const FGameplayAbilitySpec* AbilitySpec = GetAbilitySpec();
	bool bCanCast = bIsAbilityLearned;
	if (AbilitySpec)
	{
		if (OwnerAbilitySystemComponent && !UCAbilitySystemStatics::CheckAbilityCost(*AbilitySpec, *OwnerAbilitySystemComponent))
		{
			bCanCast = false;
		}
	}
	
	Icon->GetDynamicMaterial()->SetScalarParameterValue(CanCastAbilityParamName, bCanCast ? 1.0f : 0.0f);
}

void UAbilityGauge::UpgradePointUpdated(const FOnAttributeChangeData& Data)
{
	bool HasUpgradePoint = Data.NewValue > 0;
	const FGameplayAbilitySpec* AbilitySpec = GetAbilitySpec();
	if (AbilitySpec)
	{
		if (UCAbilitySystemStatics::IsAbilityAtMaxLevel(*AbilitySpec))
		{
			Icon->GetDynamicMaterial()->SetScalarParameterValue(UpgradePointAvailableParamName, 0.0f);
			return;
		}
	}
	Icon->GetDynamicMaterial()->SetScalarParameterValue(UpgradePointAvailableParamName, HasUpgradePoint ? 1.0f : 0.0f);
}

void UAbilityGauge::ManaUpdated(const FOnAttributeChangeData& Data)
{
	UpdateCanCast();
}
