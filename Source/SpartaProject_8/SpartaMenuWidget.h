#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpartaMenuWidget.generated.h"

class UButton;

UCLASS()
class SPARTAPROJECT_8_API USpartaMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void HandleStartClicked();

	UFUNCTION()
	void HandleQuitClicked();

	UFUNCTION()
	void HandleRestartClicked();

	UFUNCTION()
	void HandleMainMenuClicked();

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* Button_Start;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* Button_Quit;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* Button_Restart;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* Button_MainMenu;
};
