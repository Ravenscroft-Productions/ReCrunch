// (c) 2025-6 Ravenscroft-Productions

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "GameplayMenu.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class CRUNCH_API UGameplayMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	FOnButtonClickedEvent& GetResumeButtonClickedEventDelegate();
	void SetTitleText(const FString& NewTitle);
	
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MenuTitle;
	
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeBtn;
	
	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuBtn;
	
	UPROPERTY(meta = (BindWidget))
	UButton* QuitGameBtn;
	
	UFUNCTION()
	void BackToMainMenu();
	
	UFUNCTION()
	void QuitGame();
};
