// (c) 2025-6 Ravenscroft-Productions


#include "GAS/CAbilitySystemStatics.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"

FGameplayTag UCAbilitySystemStatics::GetBasicAttackAbilityTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack");
}

FGameplayTag UCAbilitySystemStatics::GetDeadStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Dead");
}

FGameplayTag UCAbilitySystemStatics::GetStunStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Stun");
}

FGameplayTag UCAbilitySystemStatics::GetBasicAttackInputPressedTag()
{
	return FGameplayTag::RequestGameplayTag("Ability.BasicAttack.Pressed");
}

FGameplayTag UCAbilitySystemStatics::GetAimStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Aim");
}

FGameplayTag UCAbilitySystemStatics::GetCameraShakeGameplayCueTag()
{
	return FGameplayTag::RequestGameplayTag("GameplayCue.CameraShake");
}

FGameplayTag UCAbilitySystemStatics::GetHealthFullStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Health.Full");
}

FGameplayTag UCAbilitySystemStatics::GetHealthEmptyStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Health.Empty");
}

FGameplayTag UCAbilitySystemStatics::GetManaFullStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Mana.Full");
}

FGameplayTag UCAbilitySystemStatics::GetManaEmptyStatusTag()
{
	return FGameplayTag::RequestGameplayTag("Status.Mana.Empty");
}

FGameplayTag UCAbilitySystemStatics::GetHeroRoleTag()
{
	return FGameplayTag::RequestGameplayTag("Role.Hero");
}

FGameplayTag UCAbilitySystemStatics::GetExperienceAttributeTag()
{
	return FGameplayTag::RequestGameplayTag("Attr.Experience");
}

FGameplayTag UCAbilitySystemStatics::GetGoldAttributeTag()
{
	return FGameplayTag::RequestGameplayTag("Attr.Gold");
}

bool UCAbilitySystemStatics::IsHero(const AActor* ActorToCheck)
{
	const IAbilitySystemInterface* ActorISA = Cast<IAbilitySystemInterface>(ActorToCheck);
	if (ActorISA)
	{
		UAbilitySystemComponent* ActorASC = ActorISA->GetAbilitySystemComponent();
		if (ActorASC)
		{
			return ActorASC->HasMatchingGameplayTag(GetHeroRoleTag());
		}
	}
	return false;
}

bool UCAbilitySystemStatics::IsAbilityAtMaxLevel(const FGameplayAbilitySpec& Spec)
{
	return Spec.Level >= 4;
}

float UCAbilitySystemStatics::GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability)
{
	if (!Ability) return 0.0f;
	
	const UGameplayEffect* CooldownEffect = Ability->GetCooldownGameplayEffect();
	if (!CooldownEffect) return 0.0f;
	
	float CooldownDuration = 0.0f;
	
	CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CooldownDuration);
	return CooldownDuration;
}

float UCAbilitySystemStatics::GetStaticCostForAbility(const UGameplayAbility* Ability)
{
	if (!Ability) return 0.0f;
	
	const UGameplayEffect* CostEffect = Ability->GetCostGameplayEffect();
	if (!CostEffect || CostEffect->Modifiers.Num() == 0) return 0.0f;
	
	float Cost = 0.0f;
	
	CostEffect->Modifiers[0].ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
	return FMath::Abs(Cost);
}

bool UCAbilitySystemStatics::CheckAbilityCost(const FGameplayAbilitySpec& AbilitySpec, const UAbilitySystemComponent& ASC)
{
	const UGameplayAbility* AbilityCDO = AbilitySpec.Ability;
	if (AbilityCDO)
	{
		return AbilityCDO->CheckCost(AbilitySpec.Handle, ASC.AbilityActorInfo.Get());
	}
	
	return false;
}

float UCAbilitySystemStatics::GetManaCostFor(const UGameplayAbility* AbilityCDO, const UAbilitySystemComponent& ASC, int AbilityLevel)
{
	float ManaCost = 0.0f;
	if (AbilityCDO)
	{
		UGameplayEffect* CostEffect = AbilityCDO->GetCostGameplayEffect();
		if (CostEffect)
		{
			FGameplayEffectSpecHandle EffectSpec = ASC.MakeOutgoingSpec(CostEffect->GetClass(), AbilityLevel, ASC.MakeEffectContext());
			CostEffect->Modifiers[0].ModifierMagnitude.AttemptCalculateMagnitude(*EffectSpec.Data.Get(), ManaCost);
		}
	}
	
	return FMath::Abs(ManaCost);
}

float UCAbilitySystemStatics::GetCooldownDurationFor(const UGameplayAbility* AbilityCDO, const UAbilitySystemComponent& ASC, int AbilityLevel)
{
	float CooldownDuration = 0.0f;
	if (AbilityCDO)
	{
		UGameplayEffect* CooldownEffect = AbilityCDO->GetCooldownGameplayEffect();
		if (CooldownEffect)
		{
			FGameplayEffectSpecHandle EffectSpec = ASC.MakeOutgoingSpec(CooldownEffect->GetClass(), AbilityLevel, ASC.MakeEffectContext());
			CooldownEffect->DurationMagnitude.AttemptCalculateMagnitude(*EffectSpec.Data.Get(), CooldownDuration);
		}
	}
	
	return FMath::Abs(CooldownDuration);
}

float UCAbilitySystemStatics::GetCooldownRemainingFor(const UGameplayAbility* AbilityCDO, const UAbilitySystemComponent& ASC)
{
	if (!AbilityCDO) return 0.0f;
	
	UGameplayEffect* CooldownEffect = AbilityCDO->GetCooldownGameplayEffect();
	if (!CooldownEffect) return 0.0f;
	
	FGameplayEffectQuery CooldownEffectQuery;
	CooldownEffectQuery.EffectDefinition = CooldownEffect->GetClass();
	
	float CooldownRemaining = 0.0f;
	FJsonSerializableArrayFloat CooldownTimesRemaining = ASC.GetActiveEffectsTimeRemaining(CooldownEffectQuery);
	
	for (float Remaining : CooldownTimesRemaining)
	{
		if (Remaining > CooldownRemaining)
		{
			CooldownRemaining = Remaining;
		}
	}
	
	return CooldownRemaining;
}

