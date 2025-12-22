// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	// Only called on the Server
	virtual void OnPossess(APawn* NewPawn) override;
	
	// Only called on the Client, also on the Listening Server
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	
private:
	UPROPERTY()
	ACPlayerCharacter* CPlayerCharacter;
};
