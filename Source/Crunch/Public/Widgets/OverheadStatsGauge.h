// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverheadStatsGauge.generated.h"

class UValueGauge;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class CRUNCH_API UOverheadStatsGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent);
	
private:
	UPROPERTY(meta = (BindWidget))
	UValueGauge* HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	UValueGauge* ManaBar;
};
