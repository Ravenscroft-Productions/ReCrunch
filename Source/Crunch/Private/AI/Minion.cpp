// (c) 2025-6 Ravenscroft-Productions


#include "AI/Minion.h"

#include "AbilitySystemComponent.h"
#include "GAS/CAbilitySystemStatics.h"

void AMinion::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	Super::SetGenericTeamId(NewTeamId);
	
	PickSkinBasedOnTeamID();
}

bool AMinion::IsActive() const
{
	return !GetAbilitySystemComponent()->HasMatchingGameplayTag(UCAbilitySystemStatics::GetDeadStatusTag());
}

void AMinion::Activate()
{
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(UCAbilitySystemStatics::GetDeadStatusTag()));
}

void AMinion::PickSkinBasedOnTeamID()
{
	USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId());
	if (Skin)
	{
		GetMesh()->SetSkeletalMesh(*Skin);
	}
}

void AMinion::OnRep_TeamID()
{
	PickSkinBasedOnTeamID();
}
