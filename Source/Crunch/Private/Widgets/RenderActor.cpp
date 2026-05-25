// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/RenderActor.h"

#include "Components/SceneCaptureComponent2D.h"


ARenderActor::ARenderActor()
{
	PrimaryActorTick.bCanEverTick = true;
	RootComp = CreateDefaultSubobject<USceneComponent>("Root Comp");
	SetRootComponent(RootComp);
	
	CaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("Capture Component");
	CaptureComponent->SetupAttachment(RootComp);
	
	CaptureComponent->bCaptureEveryFrame = false;
	CaptureComponent->FOVAngle = 30.0f;
}

void ARenderActor::SetRenderTarget(UTextureRenderTarget2D* RenderTarget)
{
	CaptureComponent->TextureTarget = RenderTarget;
}

void ARenderActor::UpdateRender()
{
	if (CaptureComponent)
	{
		CaptureComponent->CaptureScene();
	}
}

void ARenderActor::BeginPlay()
{
	Super::BeginPlay();
	CaptureComponent->ShowOnlyActorComponents(this);
	SetActorLocation(FVector(0.0f, 100000.0f, 0.0f));
}
