// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "RenderActor.h"
#include "SkeletalMeshRenderActor.generated.h"

UCLASS()
class CRUNCH_API ASkeletalMeshRenderActor : public ARenderActor
{
	GENERATED_BODY()
public:
	ASkeletalMeshRenderActor();
	void ConfigureSkeletalMesh(USkeletalMesh* MeshAsset, TSubclassOf<UAnimInstance> AnimBlueprint);
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Skeletal Mesh Renderer")
	USkeletalMeshComponent* MeshComp;
};
