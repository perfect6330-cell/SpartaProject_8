#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpartaProject_8GameMode.generated.h"

class ASpawnVolume;
class ASpartaProject_8GameState;
class UUserWidget;

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float TimeLimit = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	int32 ItemSpawnCount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wave")
	float SpawnInterval = 0.5f;
};

UCLASS(minimalapi)
class ASpartaProject_8GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpartaProject_8GameMode();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void QuitGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartWave(int32 WaveIndex);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndWave();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void MoveToNextLevel();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void AddScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ApplyPlayerDamage(int32 DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Game")
	void SetPlayerHP(int32 NewHP);

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetCurrentWaveIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetCurrentLevelIndex() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	float GetRemainingTime() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	TArray<FName> LevelNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	TArray<FWaveData> Waves;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	TArray<TSubclassOf<AActor>> ItemClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	FName MainMenuLevelName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	int32 InitialPlayerHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameStartWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InGameWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentLevelIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 CurrentWaveIndex;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	int32 SpawnedItemCount;

	UPROPERTY(BlueprintReadOnly, Category = "Game")
	float RemainingTime;

	FTimerHandle WaveTimerHandle;
	FTimerHandle SpawnTimerHandle;

	void InitializeDefaultWaves();
	void UpdateWaveTimer();
	void SpawnWaveItem();
	void FinishGame();
	void SyncGameState();
	void SetupUIForCurrentLevel();
	void ShowWidget(TSubclassOf<UUserWidget> WidgetClass, bool bUIOnly);
	ASpartaProject_8GameState* GetSpartaGameState() const;
};
