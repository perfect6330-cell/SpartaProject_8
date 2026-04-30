#include "SpartaProject_8GameState.h"
#include "Math/UnrealMathUtility.h"

ASpartaProject_8GameState::ASpartaProject_8GameState()
{
	Score = 0;
	CurrentLevelIndex = 1;
	CurrentWaveIndex = 1;
	RemainingTime = 0.0f;
	MaxPlayerHP = 100;
	PlayerHP = MaxPlayerHP;
	bGameOver = false;
}

int32 ASpartaProject_8GameState::GetScore() const
{
	return Score;
}

int32 ASpartaProject_8GameState::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

int32 ASpartaProject_8GameState::GetCurrentWaveIndex() const
{
	return CurrentWaveIndex;
}

float ASpartaProject_8GameState::GetRemainingTime() const
{
	return RemainingTime;
}

int32 ASpartaProject_8GameState::GetPlayerHP() const
{
	return PlayerHP;
}

int32 ASpartaProject_8GameState::GetMaxPlayerHP() const
{
	return MaxPlayerHP;
}

bool ASpartaProject_8GameState::IsGameOver() const
{
	return bGameOver;
}

void ASpartaProject_8GameState::AddScore(int32 Amount)
{
	Score = FMath::Max(0, Score + Amount);
}

void ASpartaProject_8GameState::SetScore(int32 NewScore)
{
	Score = FMath::Max(0, NewScore);
}

void ASpartaProject_8GameState::SetCurrentLevelIndex(int32 NewLevelIndex)
{
	CurrentLevelIndex = FMath::Max(1, NewLevelIndex);
}

void ASpartaProject_8GameState::SetCurrentWaveIndex(int32 NewWaveIndex)
{
	CurrentWaveIndex = FMath::Max(1, NewWaveIndex);
}

void ASpartaProject_8GameState::SetRemainingTime(float NewRemainingTime)
{
	RemainingTime = FMath::Max(0.0f, NewRemainingTime);
}

void ASpartaProject_8GameState::SetPlayerHP(int32 NewHP)
{
	PlayerHP = FMath::Clamp(NewHP, 0, MaxPlayerHP);
}

void ASpartaProject_8GameState::SetMaxPlayerHP(int32 NewMaxHP)
{
	MaxPlayerHP = FMath::Max(1, NewMaxHP);
	PlayerHP = FMath::Clamp(PlayerHP, 0, MaxPlayerHP);
}

void ASpartaProject_8GameState::SetGameOver(bool bNewGameOver)
{
	bGameOver = bNewGameOver;
}
