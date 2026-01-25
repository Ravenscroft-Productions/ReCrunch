// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilityGauge.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UAbilityGauge : public UUserWidget
{
	GENERATED_BODY()
private:
	UPROPERTY(Meta = (BindWidget))
	UImage* Icon;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CooldownCounterText;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CooldownDurationText;
	
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* CostText;
};
