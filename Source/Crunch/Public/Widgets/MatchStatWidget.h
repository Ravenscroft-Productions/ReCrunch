// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MatchStatWidget.generated.h"

class AStormCore;
class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class CRUNCH_API UMatchStatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	UImage* ProgressImage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamOneCountText;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTwoCountText;
	
	UPROPERTY()
	AStormCore* StormCore;
	
	void UpdateTeamInfluence(int TeamOneCount, int TeamTwoCount);
	void MatchFinished(AActor* ViewTarget, int WinningTeam);
};
