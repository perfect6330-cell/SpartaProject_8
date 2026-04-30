#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HpPotionItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class SPARTAPROJECT_8_API AHpPotionItem : public AActor
{
	GENERATED_BODY()

public:
	AHpPotionItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Potion")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Potion")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	int32 HealAmount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Potion")
	USoundBase* DetectSound;
};
