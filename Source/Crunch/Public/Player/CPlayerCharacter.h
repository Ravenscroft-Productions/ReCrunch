// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Crunch/Public/Character/CCharacter.h"
#include "CPlayerCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	UCameraComponent* ViewCam;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GameplayInputMappingContext;
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	
	FVector GetLookRightDir() const;
	FVector GetLookFwdDir() const;
	FVector GetMoveFwdDir() const;
};
