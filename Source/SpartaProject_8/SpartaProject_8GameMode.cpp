#include "SpartaProject_8GameMode.h"
#include "SpartaProject_8Character.h"
#include "SpartaProject_8GameState.h"
#include "SpawnVolume.h"
#include "Engine/Engine.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"

ASpartaProject_8GameMode::ASpartaProject_8GameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	GameStateClass = ASpartaProject_8GameState::StaticClass();
	CurrentLevelIndex = 1;
	CurrentWaveIndex = 0;
	SpawnedItemCount = 0;
	RemainingTime = 0.0f;
	InitialPlayerHP = 100;
	MainMenuLevelName = TEXT("MainMenu");
	CurrentWidget = nullptr;
	LevelNames.Add(TEXT("Level1"));
	LevelNames.Add(TEXT("Level2"));
	LevelNames.Add(TEXT("Level3"));
	InitializeDefaultWaves();
}

void ASpartaProject_8GameMode::BeginPlay()
{
	Super::BeginPlay();
	SyncGameState();
	SetPlayerHP(InitialPlayerHP);
	SetupUIForCurrentLevel();

	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	if (CurrentLevelName != MainMenuLevelName)
	{
		StartWave(1);
	}
}

void ASpartaProject_8GameMode::InitializeDefaultWaves()
{
	if (Waves.Num() > 0)
	{
		return;
	}

	FWaveData Wave1;
	Wave1.TimeLimit = 45.0f;
	Wave1.ItemSpawnCount = 5;
	Wave1.SpawnInterval = 0.8f;
	Waves.Add(Wave1);

	FWaveData Wave2;
	Wave2.TimeLimit = 35.0f;
	Wave2.ItemSpawnCount = 8;
	Wave2.SpawnInterval = 0.6f;
	Waves.Add(Wave2);

	FWaveData Wave3;
	Wave3.TimeLimit = 25.0f;
	Wave3.ItemSpawnCount = 12;
	Wave3.SpawnInterval = 0.4f;
	Waves.Add(Wave3);
}

void ASpartaProject_8GameMode::StartGame()
{
	if (LevelNames.Num() > 0 && !LevelNames[0].IsNone())
	{
		UGameplayStatics::OpenLevel(this, LevelNames[0]);
		return;
	}

	RestartGame();
}

void ASpartaProject_8GameMode::RestartGame()
{
	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	UGameplayStatics::OpenLevel(this, CurrentLevelName);
}

void ASpartaProject_8GameMode::ReturnToMainMenu()
{
	if (!MainMenuLevelName.IsNone())
	{
		UGameplayStatics::OpenLevel(this, MainMenuLevelName);
	}
}

void ASpartaProject_8GameMode::QuitGame()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}

void ASpartaProject_8GameMode::StartWave(int32 WaveIndex)
{
	if (Waves.Num() == 0)
	{
		InitializeDefaultWaves();
	}

	if (!Waves.IsValidIndex(WaveIndex - 1))
	{
		MoveToNextLevel();
		return;
	}

	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	CurrentWaveIndex = WaveIndex;
	SpawnedItemCount = 0;
	RemainingTime = Waves[WaveIndex - 1].TimeLimit;

	UE_LOG(LogTemp, Warning, TEXT("Wave %d 시작!"), CurrentWaveIndex);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("Wave %d 시작!"), CurrentWaveIndex));
	}

	SyncGameState();
	GetWorldTimerManager().SetTimer(WaveTimerHandle, this, &ASpartaProject_8GameMode::UpdateWaveTimer, 1.0f, true);
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ASpartaProject_8GameMode::SpawnWaveItem, Waves[WaveIndex - 1].SpawnInterval, true, 0.0f);
}

void ASpartaProject_8GameMode::UpdateWaveTimer()
{
	RemainingTime = FMath::Max(0.0f, RemainingTime - 1.0f);
	SyncGameState();

	if (RemainingTime <= 0.0f)
	{
		EndWave();
	}
}

void ASpartaProject_8GameMode::SpawnWaveItem()
{
	if (!Waves.IsValidIndex(CurrentWaveIndex - 1))
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	const FWaveData& Wave = Waves[CurrentWaveIndex - 1];
	if (SpawnedItemCount >= Wave.ItemSpawnCount)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	TArray<ASpawnVolume*> SpawnVolumes;
	for (TActorIterator<ASpawnVolume> It(GetWorld()); It; ++It)
	{
		SpawnVolumes.Add(*It);
	}

	if (SpawnVolumes.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	TArray<TSubclassOf<AActor>> ValidItemClasses;
	for (const TSubclassOf<AActor>& CandidateClass : ItemClasses)
	{
		if (CandidateClass)
		{
			ValidItemClasses.Add(CandidateClass);
		}
	}

	if (ValidItemClasses.Num() == 0 && ItemClass)
	{
		ValidItemClasses.Add(ItemClass);
	}

	if (ValidItemClasses.Num() == 0)
	{
		GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
		return;
	}

	ASpawnVolume* SelectedVolume = SpawnVolumes[FMath::RandRange(0, SpawnVolumes.Num() - 1)];
	TSubclassOf<AActor> SelectedItemClass = ValidItemClasses[FMath::RandRange(0, ValidItemClasses.Num() - 1)];
	if (SelectedVolume && SelectedItemClass)
	{
		SelectedVolume->SpawnRandomItem(SelectedItemClass);
	}

	SpawnedItemCount++;
}

void ASpartaProject_8GameMode::EndWave()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	StartWave(CurrentWaveIndex + 1);
}

void ASpartaProject_8GameMode::MoveToNextLevel()
{
	if (LevelNames.Num() == 0)
	{
		FinishGame();
		return;
	}

	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	const int32 CurrentLevelArrayIndex = LevelNames.IndexOfByKey(CurrentLevelName);
	const int32 NextLevelArrayIndex = CurrentLevelArrayIndex == INDEX_NONE ? CurrentLevelIndex : CurrentLevelArrayIndex + 1;

	if (LevelNames.IsValidIndex(NextLevelArrayIndex) && !LevelNames[NextLevelArrayIndex].IsNone())
	{
		UGameplayStatics::OpenLevel(this, LevelNames[NextLevelArrayIndex]);
		return;
	}

	FinishGame();
}

void ASpartaProject_8GameMode::FinishGame()
{
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);

	if (ASpartaProject_8GameState* SpartaGameState = GetSpartaGameState())
	{
		SpartaGameState->SetGameOver(true);
	}

	UE_LOG(LogTemp, Warning, TEXT("게임 클리어!"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("게임 클리어!"));
	}

	ShowWidget(GameOverWidgetClass, true);
}

void ASpartaProject_8GameMode::AddScore(int32 Amount)
{
	if (ASpartaProject_8GameState* SpartaGameState = GetSpartaGameState())
	{
		SpartaGameState->AddScore(Amount);
	}
}

void ASpartaProject_8GameMode::ApplyPlayerDamage(int32 DamageAmount)
{
	if (ASpartaProject_8GameState* SpartaGameState = GetSpartaGameState())
	{
		SetPlayerHP(SpartaGameState->GetPlayerHP() - DamageAmount);
	}
}

void ASpartaProject_8GameMode::SetPlayerHP(int32 NewHP)
{
	if (ASpartaProject_8GameState* SpartaGameState = GetSpartaGameState())
	{
		SpartaGameState->SetPlayerHP(NewHP);
		if (SpartaGameState->GetPlayerHP() <= 0)
		{
			SpartaGameState->SetGameOver(true);
			GetWorldTimerManager().ClearTimer(WaveTimerHandle);
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			ShowWidget(GameOverWidgetClass, true);
		}
	}
}

int32 ASpartaProject_8GameMode::GetCurrentWaveIndex() const
{
	return CurrentWaveIndex;
}

int32 ASpartaProject_8GameMode::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}

float ASpartaProject_8GameMode::GetRemainingTime() const
{
	return RemainingTime;
}

void ASpartaProject_8GameMode::SyncGameState()
{
	if (ASpartaProject_8GameState* SpartaGameState = GetSpartaGameState())
	{
		const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
		const int32 CurrentLevelArrayIndex = LevelNames.IndexOfByKey(CurrentLevelName);
		CurrentLevelIndex = CurrentLevelArrayIndex == INDEX_NONE ? FMath::Max(1, CurrentLevelIndex) : CurrentLevelArrayIndex + 1;
		SpartaGameState->SetCurrentLevelIndex(CurrentLevelIndex);
		SpartaGameState->SetCurrentWaveIndex(FMath::Max(1, CurrentWaveIndex));
		SpartaGameState->SetRemainingTime(RemainingTime);
		SpartaGameState->SetMaxPlayerHP(InitialPlayerHP);
	}
}

ASpartaProject_8GameState* ASpartaProject_8GameMode::GetSpartaGameState() const
{
	return GetGameState<ASpartaProject_8GameState>();
}

void ASpartaProject_8GameMode::SetupUIForCurrentLevel()
{
	const FName CurrentLevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
	if (CurrentLevelName == MainMenuLevelName)
	{
		ShowWidget(GameStartWidgetClass, true);
		return;
	}

	ShowWidget(InGameWidgetClass, false);
}

void ASpartaProject_8GameMode::ShowWidget(TSubclassOf<UUserWidget> WidgetClass, bool bUIOnly)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		return;
	}

	if (CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}

	if (WidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}

	if (bUIOnly)
	{
		FInputModeUIOnly InputMode;
		if (CurrentWidget)
		{
			InputMode.SetWidgetToFocus(CurrentWidget->TakeWidget());
		}
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
	else
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}
