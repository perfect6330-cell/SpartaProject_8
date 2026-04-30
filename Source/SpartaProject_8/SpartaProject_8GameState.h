#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpartaProject_8GameState.generated.h"

UCLASS()
class SPARTAPROJECT_8_API ASpartaProject_8GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ASpartaProject_8GameState();

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetCurrentLevelIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetCurrentWaveIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetRemainingTime() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetPlayerHP() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetMaxPlayerHP() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool IsGameOver() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetScore(int32 NewScore);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetCurrentLevelIndex(int32 NewLevelIndex);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetCurrentWaveIndex(int32 NewWaveIndex);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetRemainingTime(float NewRemainingTime);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetPlayerHP(int32 NewHP);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetMaxPlayerHP(int32 NewMaxHP);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetGameOver(bool bNewGameOver);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 Score;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentLevelIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentWaveIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	float RemainingTime;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 PlayerHP;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 MaxPlayerHP;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	bool bGameOver;
};
