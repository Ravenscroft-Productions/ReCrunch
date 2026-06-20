// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/CrosshairWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "GAS/CAbilitySystemStatics.h"

void UCrosshairWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	CrosshairImage->SetVisibility(ESlateVisibility::Hidden);
	
	UAbilitySystemComponent* OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwningPlayerPawn());
	if (OwnerAbilitySystemComponent)
	{
		OwnerAbilitySystemComponent->RegisterGameplayTagEvent(UCAbilitySystemStatics::GetCrosshairTag()).AddUObject(this, &UCrosshairWidget::CrosshairTagUpdated);
	}
	CachedPlayerController = GetOwningPlayer();
	
	CrosshairCanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot);
	if (!CrosshairCanvasPanelSlot)
	{
		UE_LOG(LogTemp, Error, TEXT("CrosshairWidget needs to be parented under a CanvasPanel to place itself properly"));
	}
}

void UCrosshairWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	if (CrosshairImage->GetVisibility() == ESlateVisibility::Visible)
	{
		UpdateCrosshairPosition();
	}
}

void UCrosshairWidget::CrosshairTagUpdated(const FGameplayTag Tag, int32 NewCount)
{
	CrosshairImage->SetVisibility(NewCount > 0 ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UCrosshairWidget::UpdateCrosshairPosition()
{
	if (!CachedPlayerController || !CrosshairCanvasPanelSlot) return;
	
	float ViewportScale = UWidgetLayoutLibrary::GetViewportScale(this);
	int32 SizeX, SizeY;
	CachedPlayerController->GetViewportSize(SizeX, SizeY);
	FVector2D ViewportSize = FVector2D{(float)SizeX, (float)SizeY};
	CrosshairCanvasPanelSlot->SetPosition(ViewportSize / 2.0f / ViewportScale);	
}
