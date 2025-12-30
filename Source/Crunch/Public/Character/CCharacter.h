// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCharacter.generated.h"

struct FGameplayTag;
class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacter();
	void ServerSideInit();
	void ClientSideInit();
	bool IsLocallyControlledByPlayer() const;
	// Only Called on Server
	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/***********************************************************************/
	/*                          Gameplay Ability                           */
	/***********************************************************************/
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void BindGASChangeDelegates();
	void DeadTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;
	
	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/***********************************************************************/
	/*                                 UI                                  */
	/***********************************************************************/
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* OverheadWidgetComponent;
	
	void ConfigureOverheadStatusWidget();
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatGaugeVisibilityUpdateInterval = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float OverheadStatGaugeVisibilityRangeSquared = 10000000.0f;
	
	FTimerHandle OverheadStatGaugeVisibilityUpdateTimerHandle;
	
	void UpdateOverheadGaugeVisibility();
	
	/***********************************************************************/
	/*                          Death And Respawn                          */
	/***********************************************************************/
	void StartDeathSequence();
	void Respawn();
};
