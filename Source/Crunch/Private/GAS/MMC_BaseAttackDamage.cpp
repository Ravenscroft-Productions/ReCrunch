// (c) 2025-6 Ravenscroft-Productions


#include "GAS/MMC_BaseAttackDamage.h"

#include "GAS/CAttributeSet.h"

UMMC_BaseAttackDamage::UMMC_BaseAttackDamage()
{
	DamageCaptureDef.AttributeToCapture = UCAttributeSet::GetAttackDamageAttribute();
	DamageCaptureDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	
	ArmourCaptureDef.AttributeToCapture = UCAttributeSet::GetArmourAttribute();
	ArmourCaptureDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	
	RelevantAttributesToCapture.Add(DamageCaptureDef);
	RelevantAttributesToCapture.Add(ArmourCaptureDef);
}

float UMMC_BaseAttackDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	float AttackDamage = 0.0f;
	GetCapturedAttributeMagnitude(DamageCaptureDef, Spec, EvalParams, AttackDamage);
	
	float Armour = 0.0f;
	GetCapturedAttributeMagnitude(ArmourCaptureDef, Spec, EvalParams, Armour);
	
	float Damage = AttackDamage * (1.0f - Armour/(Armour + 100));
	return -Damage;
}
