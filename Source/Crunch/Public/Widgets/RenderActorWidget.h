// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RenderActorWidget.generated.h"

class ARenderActor;
class USizeBox;
class UImage;
/**
 * 
 */
UCLASS(Abstract)
class CRUNCH_API URenderActorWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void BeginDestroy() override;
	
private:
	virtual void SpawnRenderActor() PURE_VIRTUAL(URenderActorWidget::SpawnRenderActor, );
	virtual ARenderActor* GetRenderActor() const PURE_VIRTUAL(URenderActorWidget::GetRenderActor, return nullptr; );
	void BeginRenderCapture();
	void UpdateRender();
	void StopRenderCapture();
	void ConfigureRenderActor();
	
	UPROPERTY(meta = (BindWidget))
	UImage* DisplayImage;
	
	UPROPERTY(meta = (BindWidget))
	USizeBox* RenderSizeBox;
	
	UPROPERTY(EditDefaultsOnly, Category = "Render Actor")
	FName DisplayImageRenderTargetParamName = "RenderTarget";
	
	UPROPERTY(EditDefaultsOnly, Category = "Render Actor")
	FVector2D RenderSize;
	
	UPROPERTY(EditDefaultsOnly, Category = "Render Actor")
	int FrameRate = 24;
	
	UPROPERTY()
	UTextureRenderTarget2D* RenderTarget;
	
	float RenderTickInterval;
	FTimerHandle RenderTimerHandle;
};
