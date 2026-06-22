// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

struct FGameplayEventData;
class UCanvasPanelSlot;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "View")
	FLinearColor HasTargetColour = FLinearColor::Red;
	
	UPROPERTY(EditDefaultsOnly, Category = "View")
	FLinearColor NoTargetColour = FLinearColor::White;
	
	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImage;
	
	UPROPERTY()
	UCanvasPanelSlot* CrosshairCanvasPanelSlot;
	
	UPROPERTY()
	APlayerController* CachedPlayerController;
	
	UPROPERTY()
	const AActor* AimTarget;
	
	void CrosshairTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void UpdateCrosshairPosition();
	void TargetUpdated(const FGameplayEventData* EventData);
};
