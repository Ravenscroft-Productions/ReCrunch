// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"

#include "GameplayEffectTypes.h"
#include "AttributeSet.h"
#include "Blueprint/UserWidget.h"
#include "StatsGauge.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UStatsGauge : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* Icon;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttributeText;
	
	UPROPERTY(EditAnywhere, Category = "Attribute")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, Category = "Visual")
	UTexture2D* IconTexture;
	
	void SetValue(float NewVal);
	void AttributeChanged(const FOnAttributeChangeData& Data);
	
	FNumberFormattingOptions NumberFormattingOptions;
};
