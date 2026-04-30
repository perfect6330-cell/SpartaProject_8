#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WavePickupItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SPARTAPROJECT_8_API AWavePickupItem : public AActor
{
	GENERATED_BODY()

public:
	AWavePickupItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	int32 ScoreValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	USoundBase* PickupSound;
};
