// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/ValueGauge.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UValueGauge::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ProgressBar->SetFillColorAndOpacity(BarColour);
}

void UValueGauge::SetValue(float NewValue, float NewMaxValue)
{
	if (NewMaxValue == 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Value Gauge: %s, NewMaxValue can't be 0"), *GetName());
		return;
	}
	
	float NewPercent = NewValue / NewMaxValue;
	ProgressBar->SetPercent(NewPercent);
	
	FNumberFormattingOptions FormatOps = FNumberFormattingOptions().SetMaximumFractionalDigits(0);
	
	ValueText->SetText(FText::Format(FTextFormat::FromString("{0}/{1}"), FText::AsNumber(NewValue, &FormatOps), FText::AsNumber(NewMaxValue, &FormatOps)));
}
