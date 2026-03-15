// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_AbilitySystemGenerics.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class CRUNCH_API UPDA_AbilitySystemGenerics : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FORCEINLINE TSubclassOf<UGameplayEffect> GetFullStatEffect() const { return FullStatEffect; }
	FORCEINLINE TSubclassOf<UGameplayEffect> GetDeathEffect() const { return DeathEffect; }	
	FORCEINLINE const TArray<TSubclassOf<UGameplayEffect>>& GetInitialEffects() const { return InitialEffects; }
	FORCEINLINE const TArray<TSubclassOf<UGameplayAbility>>& GetPassiveAbilities() const { return PassiveAbilities; }
	FORCEINLINE const UDataTable* GetBaseStatsDataTable() const { return BaseStatsDataTable; }
	const FRealCurve* GetExperienceCurve() const;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> FullStatEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitialEffects;
			
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TArray<TSubclassOf<UGameplayAbility>> PassiveAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Base Stats")
	UDataTable* BaseStatsDataTable;
	
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	FName ExperienceRowName = "ExperienceNeededToReachLevel";
	
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	UCurveTable* ExperienceCurveTable;
};
