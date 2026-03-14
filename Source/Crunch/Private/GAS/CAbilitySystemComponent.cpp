// (c) 2025-6 Ravenscroft-Productions


#include "GAS/CAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GAS/CAbilitySystemStatics.h"
#include "GAS/CAttributeSet.h"
#include "GAS/CHeroAttributeSet.h"

UCAbilitySystemComponent::UCAbilitySystemComponent()
{
	GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetHealthAttribute()).AddUObject(this, &UCAbilitySystemComponent::HealthUpdated);
	GetGameplayAttributeValueChangeDelegate(UCAttributeSet::GetManaAttribute()).AddUObject(this, &UCAbilitySystemComponent::ManaUpdated);
	GenericConfirmInputID = (int32)ECAbilityInputID::Confirm;
	GenericCancelInputID = (int32)ECAbilityInputID::Cancel;	
}

void UCAbilitySystemComponent::InitializeBaseAttributes()
{
	if (!AbilitySystemGenerics || !AbilitySystemGenerics->GetBaseStatsDataTable() || !GetOwner()) return;
	
	const UDataTable* BaseStatsDataTable = AbilitySystemGenerics->GetBaseStatsDataTable();
	const FHeroBaseStats* BaseStats = nullptr;
	
	for (const TPair<FName, uint8*>& DataPair : BaseStatsDataTable->GetRowMap())
	{
		BaseStats = BaseStatsDataTable->FindRow<FHeroBaseStats>(DataPair.Key, "");
		if (BaseStats && BaseStats->Class == GetOwner()->GetClass())
		{
			break;
		}
	}
	
	if (BaseStats)
	{
		SetNumericAttributeBase(UCAttributeSet::GetMaxHealthAttribute(), BaseStats->BaseMaxHealth);
		SetNumericAttributeBase(UCAttributeSet::GetMaxManaAttribute(), BaseStats->BaseMaxMana);
		SetNumericAttributeBase(UCAttributeSet::GetAttackDamageAttribute(), BaseStats->BaseAttackDamage);
		SetNumericAttributeBase(UCAttributeSet::GetArmourAttribute(), BaseStats->BaseArmour);
		SetNumericAttributeBase(UCAttributeSet::GetMoveSpeedAttribute(), BaseStats->BaseMoveSpeed);
		
		SetNumericAttributeBase(UCHeroAttributeSet::GetStrengthAttribute(), BaseStats->Strength);
		SetNumericAttributeBase(UCHeroAttributeSet::GetStrengthGrowthRateAttribute(), BaseStats->StrengthGrowthRate);
		SetNumericAttributeBase(UCHeroAttributeSet::GetIntelligenceAttribute(), BaseStats->Intelligence);
		SetNumericAttributeBase(UCHeroAttributeSet::GetIntelligenceGrowthRateAttribute(), BaseStats->IntelligenceGrowthRate);
	}
}

void UCAbilitySystemComponent::ServerSideInit()
{
	InitializeBaseAttributes();
	ApplyInitialEffects();
	GiveInitialAbilities();
}

void UCAbilitySystemComponent::ApplyInitialEffects()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
	if (!AbilitySystemGenerics) return;
	
	for (const TSubclassOf<UGameplayEffect>& EffectClass : AbilitySystemGenerics->GetInitialEffects())
	{
		AuthApplyGameplayEffect(EffectClass);
	}
}

void UCAbilitySystemComponent::GiveInitialAbilities()
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 0, static_cast<int32>(AbilityPair.Key), nullptr));
	}
	
	for (const TPair<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& AbilityPair : BasicAbilities)
	{
		GiveAbility(FGameplayAbilitySpec(AbilityPair.Value, 1, static_cast<int32>(AbilityPair.Key), nullptr));
	}
	
	if (!AbilitySystemGenerics) return;
	
	for (const TSubclassOf<UGameplayAbility>& PassiveAbility : AbilitySystemGenerics->GetPassiveAbilities())
	{
		GiveAbility(FGameplayAbilitySpec(PassiveAbility, 1, -1, nullptr));
	}
}

void UCAbilitySystemComponent::ApplyFullStatEffect()
{
	if (!AbilitySystemGenerics) return;
	
	AuthApplyGameplayEffect(AbilitySystemGenerics->GetFullStatEffect());
}

const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& UCAbilitySystemComponent::GetAbilities() const
{
	return Abilities;
}

void UCAbilitySystemComponent::AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level)
{
	if (GetOwner() && GetOwner()->HasAuthority())
	{
		FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingSpec(GameplayEffect, Level, MakeEffectContext());
		ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	}
}

void UCAbilitySystemComponent::HealthUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
	bool bFound = false;
	float MaxHealth = GetGameplayAttributeValue(UCAttributeSet::GetMaxHealthAttribute(), bFound);
	if (bFound && ChangeData.NewValue >= MaxHealth)
	{
		if (!HasMatchingGameplayTag(UCAbilitySystemStatics::GetHealthFullStatusTag()))
		{
			// This is done locally only.
			AddLooseGameplayTag(UCAbilitySystemStatics::GetHealthFullStatusTag());
		}
	}
	else
	{
		RemoveLooseGameplayTag(UCAbilitySystemStatics::GetHealthFullStatusTag());
	}
	
	if (ChangeData.NewValue <= 0)
	{
		if (!HasMatchingGameplayTag(UCAbilitySystemStatics::GetHealthEmptyStatusTag()))
		{
			AddLooseGameplayTag(UCAbilitySystemStatics::GetHealthEmptyStatusTag());
			
			if (AbilitySystemGenerics && AbilitySystemGenerics->GetDeathEffect())
			{
				AuthApplyGameplayEffect(AbilitySystemGenerics->GetDeathEffect());
			}
			
			FGameplayEventData DeadAbilityEventData;
			if (ChangeData.GEModData) DeadAbilityEventData.ContextHandle = ChangeData.GEModData->EffectSpec.GetContext();
			
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), UCAbilitySystemStatics::GetDeadStatusTag(), DeadAbilityEventData);
		}
	}
	else
	{
		RemoveLooseGameplayTag(UCAbilitySystemStatics::GetHealthEmptyStatusTag());
	}
}

void UCAbilitySystemComponent::ManaUpdated(const FOnAttributeChangeData& ChangeData)
{
	if (!GetOwner() || !GetOwner()->HasAuthority()) return;
	
	bool bFound = false;
	float MaxMana = GetGameplayAttributeValue(UCAttributeSet::GetMaxManaAttribute(), bFound);
	if (bFound && ChangeData.NewValue >= MaxMana)
	{
		if (!HasMatchingGameplayTag(UCAbilitySystemStatics::GetManaFullStatusTag()))
		{
			// This is done locally only.
			AddLooseGameplayTag(UCAbilitySystemStatics::GetManaFullStatusTag());
		}
	}
	else
	{
		RemoveLooseGameplayTag(UCAbilitySystemStatics::GetManaFullStatusTag());
	}
	
	if (ChangeData.NewValue <= 0)
	{
		if (!HasMatchingGameplayTag(UCAbilitySystemStatics::GetManaEmptyStatusTag()))
		{
			AddLooseGameplayTag(UCAbilitySystemStatics::GetManaEmptyStatusTag());
		}
	}
	else
	{
		RemoveLooseGameplayTag(UCAbilitySystemStatics::GetManaEmptyStatusTag());
	}
}
