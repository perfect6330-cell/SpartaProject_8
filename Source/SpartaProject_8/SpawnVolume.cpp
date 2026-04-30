#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	RootComponent = SpawnBox;
	SpawnBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SpawnBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpawnBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

AActor* ASpawnVolume::SpawnRandomItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass || !GetWorld())
	{
		return nullptr;
	}

	const FVector SpawnLocation = GetRandomPointInVolume();
	const FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	return GetWorld()->SpawnActor<AActor>(ItemClass, SpawnLocation, SpawnRotation, SpawnParams);
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	if (!SpawnBox)
	{
		return GetActorLocation();
	}

	const FVector Origin = SpawnBox->GetComponentLocation();
	const FVector Extent = SpawnBox->GetScaledBoxExtent();
	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);
}

UBoxComponent* ASpawnVolume::GetSpawnBox() const
{
	return SpawnBox;
}
