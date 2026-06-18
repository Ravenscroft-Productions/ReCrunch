// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class CRUNCH_API AProjectileActor : public AActor, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AProjectileActor();
	void ShootProjectile(float InSpeed, float InMaxDistance, const AActor* InTarget, FGenericTeamId InTeamId, FGameplayEffectSpecHandle InHitEffectHandle);
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void TravelMaxDistanceReached();
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Replicated)
	FGenericTeamId TeamId;
	
	UPROPERTY(Replicated)
	FVector MoveDir;
	
	UPROPERTY(Replicated)
	float ProjectileSpeed;
	
	UPROPERTY()
	const AActor* Target;
	
	FGameplayEffectSpecHandle HitEffectSpecHandle;
	FTimerHandle ShootTimerHandle;
};
