// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "CGameplayAbility.h"
#include "GA_Shoot.generated.h"

class AProjectileActor;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGA_Shoot : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_Shoot();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	TSubclassOf<UGameplayEffect> ProjectileHitEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	TSubclassOf<AProjectileActor> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	float ShootProjectileSpeed = 2000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Shoot")
	float ShootProjectileRange = 3000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Anim")
	UAnimMontage* ShootMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = "Target")
	float AimTargetCheckTimeInterval = 0.1f;
	
	UPROPERTY()
	AActor* AimTarget;
	
	UPROPERTY()
	UAbilitySystemComponent* AimTargetAbilitySystemComponent;
		
	FTimerHandle AimTargetCheckTimerHandle;
	
	static FGameplayTag GetShootTag();
	AActor* GetAimTargetIfValid() const;
	void FindAimTarget();
	void StartAimTargetCheckTimer();
	void StopAimTargetCheckTimer();
	bool HasValidTarget() const;
	bool IsTargetInRange() const;
	void TargetDeadTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
	UFUNCTION()
	void StartShooting(FGameplayEventData Payload);
	
	UFUNCTION()
	void StopShooting(FGameplayEventData Payload);
	
	UFUNCTION()
	void ShootProjectile(FGameplayEventData Payload);	
};
