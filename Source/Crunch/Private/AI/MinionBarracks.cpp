// (c) 2025-6 Ravenscroft-Productions


#include "AI/MinionBarracks.h"

#include "AI/Minion.h"
#include "GameFramework/PlayerStart.h"


AMinionBarracks::AMinionBarracks()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMinionBarracks::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnNewMinions(5);
}

void AMinionBarracks::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const APlayerStart* AMinionBarracks::GetNextSpawnSpot()
{
	if (SpawnSpots.Num() == 0) return nullptr;
	
	++NextSpawnSpotIndex;
	
	if (NextSpawnSpotIndex >= SpawnSpots.Num()) NextSpawnSpotIndex = 0;
	
	return SpawnSpots[NextSpawnSpotIndex];
}

void AMinionBarracks::SpawnNewMinions(int Amt)
{
	for (int i =0; i < Amt; i++)
	{
		FTransform SpawnTransform = GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
		{
			SpawnTransform = NextSpawnSpot->GetActorTransform();
		}
		
		AMinion* NewMinion = GetWorld()->SpawnActorDeferred<AMinion>(MinionClass, SpawnTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		NewMinion->SetGenericTeamId(BarrackTeamId);
		NewMinion->FinishSpawning(SpawnTransform);
		MinionPool.Add(NewMinion);
	}
}

