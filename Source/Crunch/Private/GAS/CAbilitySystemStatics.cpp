// (c) 2025-6 Ravenscroft-Productions


#include "GAS/CAbilitySystemStatics.h"

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