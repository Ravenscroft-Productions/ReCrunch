// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RenderActorTargetInterface.generated.h"

UINTERFACE(MinimalAPI)
class URenderActorTargetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CRUNCH_API IRenderActorTargetInterface
{
	GENERATED_BODY()

public:
	virtual FVector GetCaptureLocalPosition() const = 0;
	virtual FRotator GetCaptureLocalRotation() const = 0;
};
