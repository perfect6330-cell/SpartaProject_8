#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

public:
	ASpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	AActor* SpawnRandomItem(TSubclassOf<AActor> ItemClass);

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawn")
	UBoxComponent* GetSpawnBox() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	UBoxComponent* SpawnBox;
};
