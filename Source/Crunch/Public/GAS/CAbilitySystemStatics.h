// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "CAbilitySystemStatics.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class CRUNCH_API UCAbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static FGameplayTag GetBasicAttackAbilityTag();
	static FGameplayTag GetDeadStatusTag();
	static FGameplayTag GetStunStatusTag();
	static FGameplayTag GetBasicAttackInputPressedTag();
	static FGameplayTag GetAimStatusTag();
	static FGameplayTag GetCameraShakeGameplayCueTag();
	
	static float GetStaticCooldownDurationForAbility(const UGameplayAbility* Ability);
	static float GetStaticCostForAbility(const UGameplayAbility* Ability);
};
