// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Lazer.generated.h"

class ATargetActor_Line;
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
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetRange = 4000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float DetectionCylinderRadius = 30.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetingInterval = 0.3f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> HitDamageEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	float HitPushSpeed = 3000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<UGameplayEffect> OngoingConsumptionEffect;
	
	FActiveGameplayEffectHandle OngoingConsumptionEffectHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* LazerMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<ATargetActor_Line> LazerTargetActorClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	FName TargetActorAttachSocketName = "Lazer";
	
	UFUNCTION()
	void ShootLazer(FGameplayEventData Payload);
	
	UFUNCTION()
	void TargetReceived(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	
	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
};
