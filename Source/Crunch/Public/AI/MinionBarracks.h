// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "MinionBarracks.generated.h"

class AMinion;

UCLASS()
class CRUNCH_API AMinionBarracks : public AActor
{
	GENERATED_BODY()

public:
	AMinionBarracks();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamId;
	
	UPROPERTY()
	TArray<AMinion*> MinionPool;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AMinion> MinionClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<APlayerStart*> SpawnSpots;
	
	int NextSpawnSpotIndex = -1;
	
	const APlayerStart* GetNextSpawnSpot();
	
	void SpawnNewMinions(int Amt);
};
