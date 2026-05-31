// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "StormCore.generated.h"

UCLASS()
class CRUNCH_API AStormCore : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AStormCore();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
