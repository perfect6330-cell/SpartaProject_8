#include "HpPotionItem.h"
#include "SpartaProject_8Character.h"
#include "SpartaProject_8GameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AHpPotionItem::AHpPotionItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->InitSphereRadius(45.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealAmount = 5;
	DetectSound = nullptr;
}

void AHpPotionItem::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &AHpPotionItem::OnOverlapBegin);
}

void AHpPotionItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASpartaProject_8Character* Character = Cast<ASpartaProject_8Character>(OtherActor);
	if (!Character)
	{
		return;
	}

	if (DetectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DetectSound, GetActorLocation());
	}

	Character->HealHP(HealAmount);

	if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->SetPlayerHP(Character->GetHP());
	}

	Destroy();
}
