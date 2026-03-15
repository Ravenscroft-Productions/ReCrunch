// (c) 2025-6 Ravenscroft-Productions


#include "GAS/PDA_AbilitySystemGenerics.h"

const FRealCurve* UPDA_AbilitySystemGenerics::GetExperienceCurve() const
{
	return ExperienceCurveTable->FindCurve(ExperienceRowName, "");
}
