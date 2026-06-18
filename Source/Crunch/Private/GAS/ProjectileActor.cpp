// (c) 2025-6 Ravenscroft-Productions


#include "GAS/ProjectileActor.h"

#include "Net/UnrealNetwork.h"


AProjectileActor::AProjectileActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>("Root Comp");
	SetRootComponent(RootComp);
	bReplicates = true;
}

void AProjectileActor::ShootProjectile(float InSpeed, float InMaxDistance, const AActor* InTarget, FGenericTeamId InTeamId, FGameplayEffectSpecHandle InHitEffectHandle)
{
	Target = InTarget;
	ProjectileSpeed = InSpeed;
	
	FRotator OwnerViewRot = GetActorRotation();
	SetGenericTeamId(InTeamId);
	
	if (GetOwner())
	{
		FVector OwnerViewLoc;
		GetOwner()->GetActorEyesViewPoint(OwnerViewLoc, OwnerViewRot);
	}
	
	MoveDir = OwnerViewRot.Vector();	
	HitEffectSpecHandle = InHitEffectHandle;
	
	float TravelMaxTime = InMaxDistance / InSpeed;
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AProjectileActor::TravelMaxDistanceReached, TravelMaxTime);
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();	
}

void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		if (Target)
		{
			MoveDir = (Target->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		}
	}
	
	SetActorLocation(GetActorLocation() + MoveDir * ProjectileSpeed * DeltaTime);
}

void AProjectileActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AProjectileActor, MoveDir);
	DOREPLIFETIME(AProjectileActor, TeamId);
	DOREPLIFETIME(AProjectileActor, ProjectileSpeed);
}

void AProjectileActor::TravelMaxDistanceReached()
{
	Destroy();
}

void AProjectileActor::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamId = NewTeamID;
}

