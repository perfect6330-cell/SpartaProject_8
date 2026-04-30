#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpartaInGameWidget.generated.h"

class UTextBlock;

UCLASS()
class SPARTAPROJECT_8_API USpartaInGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "UI")
	FText GetHPText() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	FText GetScoreText() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	FText GetTimeText() const;

	UFUNCTION(BlueprintPure, Category = "UI")
	FText GetWaveText() const;

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Text_HP;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Text_Score;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Text_Timer;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* Text_Wave;

	void RefreshTexts();
};
