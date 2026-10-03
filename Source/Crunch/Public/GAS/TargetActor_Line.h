// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TargetActor_Line.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class CRUNCH_API ATargetActor_Line : public AGameplayAbilityTargetActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	ATargetActor_Line();
	void ConfigureTargetSetting(float NewTargetRange, float NewDetectionCylinderRadius, float NewTargetingInterval, FGenericTeamId OwnerTeamId, bool bShouldDrawDebug);
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	FORCEINLINE virtual FGenericTeamId GetGenericTeamId() const override{ return TeamId; }
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
private:
	UPROPERTY(Replicated)
	float TargetRange;
	
	UPROPERTY(Replicated)
	float DetectionCylinderRadius;
	
	UPROPERTY()
	float TargetingInterval;
	
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;
	
	UPROPERTY()
	bool bDrawDebug;
	
	UPROPERTY(Replicated)
	const AActor* AvatarActor;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USceneComponent* RootComp;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	UNiagaraComponent* LazerVFX;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Component")
	USphereComponent* TargetEndDetectionSphere;
};
