// (c) 2025-6 Ravenscroft-Productions


#include "GAS/CAbilitySystemStatics.h"

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
