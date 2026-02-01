// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Crunch/Public/Character/CCharacter.h"
#include "GAS/CGameplayAbilityTypes.h"
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
		
	FVector GetLookRightDir() const;
	FVector GetLookFwdDir() const;
	FVector GetMoveFwdDir() const;
	
	/***********************************************************************/
	/*                          Gameplay Ability                           */
	/***********************************************************************/
	virtual void OnAimStateChanged(bool bIsAiming) override;
	
	/***********************************************************************/
	/*                               Input                                 */
	/***********************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECAbilityInputID, UInputAction*> GameplayAbilityInputActions;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GameplayInputMappingContext;
	
	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID);
	void SetInputEnabledFromPlayerController(bool bEnabled);
	
	/***********************************************************************/
	/*                                 Stun                                */
	/***********************************************************************/
	virtual void OnStun() override;
	virtual void OnRecoverFromStun() override;
	
	/***********************************************************************/
	/*                           Death and Respawn                         */
	/***********************************************************************/
	virtual void OnDead() override;
	virtual void OnRespawn() override;
	
	/***********************************************************************/
	/*                              Camera View                            */
	/***********************************************************************/
	UPROPERTY(EditDefaultsOnly, Category = "View")
	FVector CameraAimLocalOffset;
	
	UPROPERTY(EditDefaultsOnly, Category = "View")
	float CameraLerpSpeed = 20.0f;
	
	FTimerHandle CameraLerpTimerHandle;
	
	void LerpCameraToLocalOffsetLocation(const FVector& Goal);
	void TickCameraLocalOffsetLerp(FVector Goal);
};
