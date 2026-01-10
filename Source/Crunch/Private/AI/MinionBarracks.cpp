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
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(SpawnIntervalTimerHandle, this, &AMinionBarracks::SpawnNewGroup, GroupSpawnInterval, true);
	}
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

void AMinionBarracks::SpawnNewGroup()
{
	int i = MinionsPerGroup;
	
	while (i > 0)
	{
		FTransform SpawnTransform = GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
		{
			SpawnTransform = NextSpawnSpot->GetActorTransform();
		}
		
		AMinion* NextAvailableMinion = GetNextAvailableMinion();
		if (!NextAvailableMinion) break;
		
		NextAvailableMinion->SetActorTransform(SpawnTransform);
		NextAvailableMinion->Activate();
		--i;
	}
	
	SpawnNewMinions(i);
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
		NewMinion->SetGoal(Goal);
		MinionPool.Add(NewMinion);
	}
}

AMinion* AMinionBarracks::GetNextAvailableMinion() const
{
	for (AMinion* Minion : MinionPool)
	{
		if (!Minion->IsActive()) return Minion;
	}
	
	return nullptr;
}

