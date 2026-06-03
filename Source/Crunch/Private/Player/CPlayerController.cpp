// (c) 2025-6 Ravenscroft-Productions


#include "Crunch/Public/Player/CPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Net/UnrealNetwork.h"
#include "Widgets/GameplayWidget.h"
#include "Player/CPlayerCharacter.h"

void ACPlayerController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(NewPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ServerSideInit();
		CPlayerCharacter->SetGenericTeamId(TeamID);
	}
}

void ACPlayerController::AcknowledgePossession(APawn* NewPawn)
{
	Super::AcknowledgePossession(NewPawn);
	
	CPlayerCharacter = Cast<ACPlayerCharacter>(NewPawn);
	if (CPlayerCharacter)
	{
		CPlayerCharacter->ClientSideInit();
		SpawnGameplayWidget();
	}
}

void ACPlayerController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}

FGenericTeamId ACPlayerController::GetGenericTeamId() const
{
	return TeamID;
}

void ACPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ACPlayerController, TeamID);
}

void ACPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (InputSubsystem)
	{
		InputSubsystem->RemoveMappingContext(UIInputMapping);
		InputSubsystem->AddMappingContext(UIInputMapping, 1);
	}
	
	UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComp)
	{
		EnhancedInputComp->BindAction(ShopToggleInputAction, ETriggerEvent::Triggered, this, &ACPlayerController::ToggleShop);
		EnhancedInputComp->BindAction(ToggleGameplayMenuAction, ETriggerEvent::Triggered, this, &ACPlayerController::ToggleGameplayMenu);
	}
}

void ACPlayerController::MatchFinished(AActor* ViewTarget, int WinningTeam)
{
	if (!HasAuthority()) return;
	
	CPlayerCharacter->DisableInput(this);
	Client_MatchFinished(ViewTarget, WinningTeam);	
}

void ACPlayerController::SpawnGameplayWidget()
{
	if (!IsLocalPlayerController()) return;
	
	GameplayWidget = CreateWidget<UGameplayWidget>(this, GameplayWidgetClass);
	if (GameplayWidget)
	{
		GameplayWidget->AddToViewport();
		GameplayWidget->ConfigureAbilities(CPlayerCharacter->GetAbilities());
	}
}

void ACPlayerController::ShowWinLoseState()
{
	if (GameplayWidget)
	{
		GameplayWidget->ShowGameplayMenu();
	}
}

void ACPlayerController::Client_MatchFinished_Implementation(AActor* ViewTarget, int WinningTeam)
{
	SetViewTargetWithBlend(ViewTarget, MatchFinishViewBlendTimeDuration);
	FString WinLoseMsg = "You Won!";
	if (GetGenericTeamId() != WinningTeam)
	{
		WinLoseMsg = "You Lost!";
	}
	GameplayWidget->SetGameplayMenuTitle(WinLoseMsg);
	FTimerHandle ShowWinLoseStateTimerHandle;
	GetWorldTimerManager().SetTimer(ShowWinLoseStateTimerHandle, this, &ACPlayerController::ShowWinLoseState, MatchFinishViewBlendTimeDuration);
}

void ACPlayerController::ToggleShop()
{
	if (GameplayWidget)
	{
		GameplayWidget->ToggleShop();
	}
}

void ACPlayerController::ToggleGameplayMenu()
{
	if (GameplayWidget)
	{
		GameplayWidget->ToggleGameplayMenu();
	}
}
