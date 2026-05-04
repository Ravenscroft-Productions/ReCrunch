// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplineWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API USplineWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetupSpline(const UUserWidget* InStartWidget, const UUserWidget* InEndWidget, const FVector2D& InStartPortLocalCoord, const FVector2D& InEndPortLocalCoord, const FVector2D& InStartPortDirection, const FVector2D& InEndPortDirection);
	void SetSplineStyle(const FLinearColor InColour, float InThickness);
	
private:
	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;
	
	UPROPERTY()
	const UUserWidget* StartWidget;
	
	UPROPERTY()
	const UUserWidget* EndWidget;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	FVector2D StartPortDirection;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	FVector2D EndPortDirection;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	FLinearColor Colour = FLinearColor::White;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	float Thickness = 3.0f;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	FVector2D TestStartPos;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	FVector2D TestEndPos = FVector2D{100, 100};
	
	FVector2D StartPortLocalCoord;
	FVector2D EndPortLocalCoord;
};
