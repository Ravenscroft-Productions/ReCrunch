// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

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
	void SetValue(float NewValue, float NewMaxValue);
	
private:
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColour;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UProgressBar* ProgressBar;
	
	UPROPERTY(VisibleAnywhere, meta=(BindWidget))
	UTextBlock* ValueText;	
};
