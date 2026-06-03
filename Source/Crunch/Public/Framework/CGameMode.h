// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/GameModeBase.h"
#include "CGameMode.generated.h"

class AStormCore;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
	virtual void StartPlay() override;
	
private:
	FGenericTeamId GetTeamIDForPlayer(const APlayerController* PlayerController) const;
	AActor* FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const;
	AStormCore* GetStormCore() const;
	void MatchFinished(AActor* ViewTarget, int WinningTeam);
	
	UPROPERTY(EditDefaultsOnly, Category="Team")
	TMap<FGenericTeamId, FName> TeamStartSpotTagMap;
};
