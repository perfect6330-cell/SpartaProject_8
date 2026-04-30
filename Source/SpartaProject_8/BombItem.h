#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BombItem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;

UCLASS()
class SPARTAPROJECT_8_API ABombItem : public AActor
{
	GENERATED_BODY()

public:
	ABombItem();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void Explode();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bomb")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb")
	float ExplosionDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb")
	UParticleSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb")
	USoundBase* DetectSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bomb")
	USoundBase* ExplosionSound;

	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappedCharacters;

	FTimerHandle ExplosionTimerHandle;
	bool bExplosionStarted;
};
