// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

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
	UPROPERTY(meta = (BindWidget))
	UImage* CrosshairImage;
	
	UPROPERTY()
	UCanvasPanelSlot* CrosshairCanvasPanelSlot;
	
	UPROPERTY()
	APlayerController* CachedPlayerController;
	
	void CrosshairTagUpdated(const FGameplayTag Tag, int32 NewCount);
	void UpdateCrosshairPosition();
};
