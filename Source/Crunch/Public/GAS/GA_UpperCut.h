// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_UpperCut.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_UpperCut : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	TSubclassOf<UGameplayEffect> LaunchDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* UpperCutMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetSweepSphereRadius = 80.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float UpperCutLaunchSpeed = 1000.0f;
	
	static FGameplayTag GetUpperCutLaunchTag();
	
	UFUNCTION()
	void StartLaunching(FGameplayEventData EventData);
	
	UFUNCTION()
	void HandleComboChangeEvent(FGameplayEventData EventData);
	
	FName NextComboName;
	
	bool bHasLaunched = false;
};
