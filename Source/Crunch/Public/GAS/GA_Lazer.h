// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Lazer.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Lazer : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	static FGameplayTag GetShootTag();
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> OngoingConsumptionEffect;
	
	FActiveGameplayEffectHandle OngoingConsumptionEffectHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* LazerMontage;
	
	UFUNCTION()
	void ShootLazer(FGameplayEventData Payload);
	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
};
