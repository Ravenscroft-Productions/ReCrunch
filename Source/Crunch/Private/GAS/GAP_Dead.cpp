// (c) 2025-6 Ravenscroft-Productions


#include "GAS/GAP_Dead.h"

#include "Engine/OverlapResult.h"
#include "GAS/CAbilitySystemStatics.h"

UGAP_Dead::UGAP_Dead()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
	
	FAbilityTriggerData TriggerData;
	TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	TriggerData.TriggerTag = UCAbilitySystemStatics::GetDeadStatusTag();
	
	AbilityTriggers.Add(TriggerData);
	
	ActivationBlockedTags.RemoveTag(UCAbilitySystemStatics::GetStunStatusTag());
}

void UGAP_Dead::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (K2_HasAuthority())
	{
		AActor* Killer = TriggerEventData->ContextHandle.GetEffectCauser();
		if (Killer)
		{
			UE_LOG(LogTemp, Warning, TEXT("I am Dead, the Killer is: %s"), *Killer->GetName());
		}
		
		TArray<AActor*> RewardTargets = GetRewardTargets();
		for (const AActor* RewardTarget : RewardTargets)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found Reward Target: %s"), *RewardTarget->GetName());
		}
	}
}

TArray<AActor*> UGAP_Dead::GetRewardTargets() const
{
	TSet<AActor*> OutActors;
	
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!AvatarActor || !GetWorld()) return OutActors.Array();
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(RewardRange);
	
	if (GetWorld()->OverlapMultiByObjectType(OverlapResults, AvatarActor->GetActorLocation(), FQuat::Identity, ObjectQueryParams, CollisionShape))
	{
		for (const FOverlapResult& OverlapResult : OverlapResults)
		{
			const IGenericTeamAgentInterface* OtherTeamInterface = Cast<IGenericTeamAgentInterface>(OverlapResult.GetActor());
			if (!OtherTeamInterface || OtherTeamInterface->GetTeamAttitudeTowards(*AvatarActor) != ETeamAttitude::Hostile) continue;
			
			if (!UCAbilitySystemStatics::IsHero(OverlapResult.GetActor())) continue;
			
			OutActors.Add(OverlapResult.GetActor());
		}
	}
	return OutActors.Array();
}
