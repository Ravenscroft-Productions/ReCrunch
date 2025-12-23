// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CCharacter.generated.h"

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
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;
	
	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/***********************************************************************/
	/*                                 UI                                  */
	/***********************************************************************/
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UWidgetComponent* OverheadWidgetComponent;
	
	void ConfigureOverheadStatusWidget();
};
