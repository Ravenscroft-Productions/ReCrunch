// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
class UGameplayWidget;
class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	// Only called on the Server
	virtual void OnPossess(APawn* NewPawn) override;
	
	// Only called on the Client, also on the Listening Server
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	
	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	
	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SetupInputComponent() override;
	
private:
	void SpawnGameplayWidget();
	
	UPROPERTY()
	ACPlayerCharacter* CPlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	UGameplayWidget* GameplayWidget;
	
	UPROPERTY(Replicated)
	FGenericTeamId TeamID;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* UIInputMapping;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* ShopToggleInputAction;
	
	UFUNCTION()
	void ToggleShop();
};
