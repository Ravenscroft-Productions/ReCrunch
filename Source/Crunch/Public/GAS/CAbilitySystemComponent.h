// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CGameplayAbilityTypes.h"
#include "CAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	UCAbilitySystemComponent();
	void InitializeBaseAttributes();
	void ServerSideInit();
	void ApplyFullStatEffect();
	// Get the Abilities that are unique for the Avatar Actor, this does not include generic/basic ones
	const TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>>& GetAbilities() const;
	
private:
	void ApplyInitialEffects();
	void GiveInitialAbilities();
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level = 1);
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	void ManaUpdated(const FOnAttributeChangeData& ChangeData);
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> FullStatEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Base Stats")
	UDataTable* BaseStatsDataTable;
};