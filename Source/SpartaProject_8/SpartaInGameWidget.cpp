#include "SpartaInGameWidget.h"
#include "SpartaProject_8GameState.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void USpartaInGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	RefreshTexts();
}

FText USpartaInGameWidget::GetHPText() const
{
	if (const ASpartaProject_8GameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaProject_8GameState>() : nullptr)
	{
		return FText::FromString(FString::Printf(TEXT("HP: %d / %d"), SpartaGameState->GetPlayerHP(), SpartaGameState->GetMaxPlayerHP()));
	}

	return FText::FromString(TEXT("HP: 0 / 0"));
}

FText USpartaInGameWidget::GetScoreText() const
{
	if (const ASpartaProject_8GameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaProject_8GameState>() : nullptr)
	{
		return FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameState->GetScore()));
	}

	return FText::FromString(TEXT("Score: 0"));
}

FText USpartaInGameWidget::GetTimeText() const
{
	if (const ASpartaProject_8GameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaProject_8GameState>() : nullptr)
	{
		return FText::FromString(FString::Printf(TEXT("Time: %d"), FMath::CeilToInt(SpartaGameState->GetRemainingTime())));
	}

	return FText::FromString(TEXT("Time: 0"));
}

FText USpartaInGameWidget::GetWaveText() const
{
	if (const ASpartaProject_8GameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaProject_8GameState>() : nullptr)
	{
		return FText::FromString(FString::Printf(TEXT("Wave: %d"), SpartaGameState->GetCurrentWaveIndex()));
	}

	return FText::FromString(TEXT("Wave: 1"));
}

void USpartaInGameWidget::RefreshTexts()
{
	if (Text_HP)
	{
		Text_HP->SetText(GetHPText());
	}

	if (Text_Score)
	{
		Text_Score->SetText(GetScoreText());
	}

	if (Text_Timer)
	{
		Text_Timer->SetText(GetTimeText());
	}

	if (Text_Wave)
	{
		Text_Wave->SetText(GetWaveText());
	}
}
