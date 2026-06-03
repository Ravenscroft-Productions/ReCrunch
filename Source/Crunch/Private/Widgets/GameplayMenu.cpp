// (c) 2025-6 Ravenscroft-Productions


#include "Widgets/GameplayMenu.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameplayMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	MainMenuBtn->OnClicked.AddDynamic(this, &UGameplayMenu::BackToMainMenu);
	QuitGameBtn->OnClicked.AddDynamic(this, &UGameplayMenu::QuitGame);	
}

FOnButtonClickedEvent& UGameplayMenu::GetResumeButtonClickedEventDelegate()
{
	return ResumeBtn->OnClicked;
}

void UGameplayMenu::BackToMainMenu()
{	
}

void UGameplayMenu::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
