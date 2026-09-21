// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TargetActor_Line.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class CRUNCH_API ATargetActor_Line : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	ATargetActor_Line();
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* RootComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UNiagaraComponent* LazerVFX;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USphereComponent* TargetEndDetectionSphere;
	
	const AActor* AvatarActor;
};
