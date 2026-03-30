// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericTeamAgentInterface.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendTargetGroup.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UAN_SendTargetGroup : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTagContainer TriggerGameplayCueTags;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	TEnumAsByte<ETeamAttitude::Type> TargetTeam = ETeamAttitude::Hostile;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	float SphereSweepRadius = 60.0f;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	bool bDrawDebug = true;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	bool bIgnoreOwner = true;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;
	
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	TArray<FName> TargetSocketNames;
	
	void SendLocalGameplayCue(const FHitResult& HitResult) const;
};
