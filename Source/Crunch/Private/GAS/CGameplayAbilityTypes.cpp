// (c) 2025-6 Ravenscroft-Productions


#include "GAS/CGameplayAbilityTypes.h"

FGenericDamageEffectDef::FGenericDamageEffectDef()
	:DamageEffect{nullptr},
	PushVelocity{0.0f}
{	
}

FHeroBaseStats::FHeroBaseStats()
	:Class{nullptr},
	Strength{0.0f},
	Intelligence{0.0f},
	StrengthGrowthRate{0.0f},
	IntelligenceGrowthRate{0.0f},
	BaseMaxHealth{0.0f},
	BaseMaxMana{0.0f},
	BaseAttackDamage{0.0f},
	BaseArmour{0.0f},
	BaseMoveSpeed{0.0f}
{
}
