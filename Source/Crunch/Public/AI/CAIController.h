// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

class UAISenseConfig_Sight;

UCLASS()
class CRUNCH_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();
	virtual void OnPossess(APawn* NewPawn) override;
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "AI Behaviour")
	UBehaviorTree* BehaviourTree;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI Behaviour")
	FName TargetBlackboardKeyName = "Target";
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAISenseConfig_Sight* SightConfig;
	
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);
	
	UFUNCTION()
	void TargetForgotten(AActor* ForgottenActor);
	
	const UObject* GetCurrentTarget() const;
	void SetCurrentTarget(AActor* NewTarget);
	AActor* GetNextPerceivedActor() const;
};
