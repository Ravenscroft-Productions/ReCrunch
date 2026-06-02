// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/MatchStatWidget.h"

#include "Components/TextBlock.h"
#include "Framework/StormCore.h"
#include "Kismet/GameplayStatics.h"

void UMatchStatWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	StormCore = Cast<AStormCore>(UGameplayStatics::GetActorOfClass(this, AStormCore::StaticClass()));
	if (StormCore)
	{
		StormCore->OnTeamInfluencerCountUpdated.AddUObject(this, &UMatchStatWidget::UpdateTeamInfluence);
		StormCore->OnGoalReached.AddUObject(this, &UMatchStatWidget::MatchFinished);
	}
}

void UMatchStatWidget::UpdateTeamInfluence(int TeamOneCount, int TeamTwoCount)
{
	TeamOneCountText->SetText(FText::AsNumber(TeamOneCount));
	TeamTwoCountText->SetText(FText::AsNumber(TeamTwoCount));
}

void UMatchStatWidget::MatchFinished(AActor* ViewTarget, int WinningTeam)
{
	
}
