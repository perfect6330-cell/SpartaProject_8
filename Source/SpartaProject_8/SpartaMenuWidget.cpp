#include "SpartaMenuWidget.h"
#include "SpartaProject_8GameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USpartaMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Start)
	{
		Button_Start->OnClicked.AddDynamic(this, &USpartaMenuWidget::HandleStartClicked);
	}

	if (Button_Quit)
	{
		Button_Quit->OnClicked.AddDynamic(this, &USpartaMenuWidget::HandleQuitClicked);
	}

	if (Button_Restart)
	{
		Button_Restart->OnClicked.AddDynamic(this, &USpartaMenuWidget::HandleRestartClicked);
	}

	if (Button_MainMenu)
	{
		Button_MainMenu->OnClicked.AddDynamic(this, &USpartaMenuWidget::HandleMainMenuClicked);
	}
}

void USpartaMenuWidget::HandleStartClicked()
{
	if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->StartGame();
	}
}

void USpartaMenuWidget::HandleQuitClicked()
{
	if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->QuitGame();
	}
}

void USpartaMenuWidget::HandleRestartClicked()
{
	if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->RestartGame();
	}
}

void USpartaMenuWidget::HandleMainMenuClicked()
{
	if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->ReturnToMainMenu();
	}
}
