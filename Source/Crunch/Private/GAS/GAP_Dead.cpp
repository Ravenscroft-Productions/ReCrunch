// (c) 2025-6 Ravenscroft-Productions


#include "GAS/GAP_Dead.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Engine/OverlapResult.h"
#include "GAS/CAbilitySystemStatics.h"
#include "GAS/CHeroAttributeSet.h"

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
		if (!Killer || !UCAbilitySystemStatics::IsHero(Killer))
		{
			Killer = nullptr;
		}
		
		TArray<AActor*> RewardTargets = GetRewardTargets();
		if (RewardTargets.Num() == 0 && !Killer)
		{
			K2_EndAbility();
			return;
		}
		
		if (Killer && !RewardTargets.Contains(Killer))
		{
			RewardTargets.Add(Killer);
		}
		
		bool bFound = false;
		float SelfExperience = GetAbilitySystemComponentFromActorInfo_Ensured()->GetGameplayAttributeValue(UCHeroAttributeSet::GetExperienceAttribute(), bFound);
		
		float TotalExperienceReward = BaseExperienceReward + ExperienceRewardPerExperience * SelfExperience;
		float TotalGoldReward = BaseGoldReward + GoldRewardPerExperience * SelfExperience;
		
		if (Killer)
		{
			float KillerExperienceReward = TotalExperienceReward * KillerRewardPortion;
			float KillerGoldReward = TotalGoldReward * KillerRewardPortion;
			
			FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(RewardEffect);
			EffectSpec.Data->SetSetByCallerMagnitude(UCAbilitySystemStatics::GetExperienceAttributeTag(), KillerExperienceReward);
			EffectSpec.Data->SetSetByCallerMagnitude(UCAbilitySystemStatics::GetGoldAttributeTag(), KillerGoldReward);
			
			K2_ApplyGameplayEffectSpecToTarget(EffectSpec, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Killer));
			
			TotalExperienceReward -= KillerExperienceReward;
			TotalGoldReward -= KillerGoldReward;
		}
		
		float ExperiencePerTarget = TotalExperienceReward / RewardTargets.Num();
		float GoldPerTarget = TotalGoldReward / RewardTargets.Num();
		
		FGameplayEffectSpecHandle EffectSpec = MakeOutgoingGameplayEffectSpec(RewardEffect);
		EffectSpec.Data->SetSetByCallerMagnitude(UCAbilitySystemStatics::GetExperienceAttributeTag(), ExperiencePerTarget);
		EffectSpec.Data->SetSetByCallerMagnitude(UCAbilitySystemStatics::GetGoldAttributeTag(), GoldPerTarget);
		
		K2_ApplyGameplayEffectSpecToTarget(EffectSpec, UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(RewardTargets, true));
		K2_EndAbility();
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
