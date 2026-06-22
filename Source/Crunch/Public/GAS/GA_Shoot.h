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
	
	static FGameplayTag GetShootTag();
	AActor* GetAimTargetIfValid() const;
	
	UFUNCTION()
	void StartShooting(FGameplayEventData Payload);
	
	UFUNCTION()
	void StopShooting(FGameplayEventData Payload);
	
	UFUNCTION()
	void ShootProjectile(FGameplayEventData Payload);	
};
