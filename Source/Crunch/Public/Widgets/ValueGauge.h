// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "GameplayEffectTypes.h"
#include "ValueGauge.generated.h"

class UAbilitySystemComponent;
class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class CRUNCH_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	void SetAndBindToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);
	void SetValue(float NewValue, float NewMaxValue);
	
private:
	void ValueChanged(const FOnAttributeChangeData& ChangedData);
	void MaxValueChanged(const FOnAttributeChangeData& ChangedData);
	
	float CachedValue;
	float CachedMaxValue;
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColour;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* ValueText;	
};
