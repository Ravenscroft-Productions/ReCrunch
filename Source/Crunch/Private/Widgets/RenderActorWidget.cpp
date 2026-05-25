// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/RenderActorWidget.h"

#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Widgets/RenderActor.h"

void URenderActorWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	RenderSizeBox->SetWidthOverride(RenderSize.X);
	RenderSizeBox->SetHeightOverride(RenderSize.Y);
}

void URenderActorWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SpawnRenderActor();
	ConfigureRenderActor();
	BeginRenderCapture();
}

void URenderActorWidget::BeginDestroy()
{
	StopRenderCapture();
	
	Super::BeginDestroy();
}

void URenderActorWidget::BeginRenderCapture()
{
	RenderTickInterval = 1.0f / (float)FrameRate;
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(RenderTimerHandle, this, &URenderActorWidget::UpdateRender, RenderTickInterval, true);
	}
}

void URenderActorWidget::UpdateRender()
{
	if (GetRenderActor())
	{
		GetRenderActor()->UpdateRender();
	}
}

void URenderActorWidget::StopRenderCapture()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(RenderTimerHandle);
	}	
}

void URenderActorWidget::ConfigureRenderActor()
{
	if (!GetRenderActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Render Actor, Nothing will be rendered"));
		return;
	}
	
	RenderTarget = NewObject<UTextureRenderTarget2D>(this);
	RenderTarget->InitAutoFormat(RenderSize.X, RenderSize.Y);
	RenderTarget->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
	GetRenderActor()->SetRenderTarget(RenderTarget);
	
	UMaterialInstanceDynamic* DisplayImageDynamicMaterial = DisplayImage->GetDynamicMaterial();
	if (DisplayImageDynamicMaterial)
	{
		DisplayImageDynamicMaterial->SetTextureParameterValue(DisplayImageRenderTargetParamName, RenderTarget);
	}
}
