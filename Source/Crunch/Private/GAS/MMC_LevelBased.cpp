// (c) 2025-6 Ravenscroft-Productions


#include "GAS/MMC_LevelBased.h"

#include "GAS/CAttributeSet.h"
#include "GAS/CHeroAttributeSet.h"

UMMC_LevelBased::UMMC_LevelBased()
{
	LevelCaptureDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	LevelCaptureDefinition.AttributeToCapture = UCHeroAttributeSet::GetLevelAttribute();
	
	RelevantAttributesToCapture.Add(LevelCaptureDefinition);
}

float UMMC_LevelBased::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	UAbilitySystemComponent* ASC = Spec.GetContext().GetInstigatorAbilitySystemComponent();
	if (!ASC) return 0.0f;
	
	float Level = 0.0f;
	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	GetCapturedAttributeMagnitude(LevelCaptureDefinition, Spec, EvalParams, Level);
	
	bool bFound;
	float RateAttributeVal = ASC->GetGameplayAttributeValue(RateAttribute, bFound);
	if (!bFound) return 0.0f;
	
	return (Level - 1) * RateAttributeVal;
}
