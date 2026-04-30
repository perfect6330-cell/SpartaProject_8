#include "BombItem.h"
#include "SpartaProject_8Character.h"
#include "SpartaProject_8GameMode.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABombItem::ABombItem()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = Collision;
	Collision->InitSphereRadius(180.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Damage = 30;
	ExplosionDelay = 3.0f;
	bExplosionStarted = false;
}

void ABombItem::BeginPlay()
{
	Super::BeginPlay();
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABombItem::OnOverlapBegin);
	Collision->OnComponentEndOverlap.AddDynamic(this, &ABombItem::OnOverlapEnd);
}

void ABombItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherActor->IsA<ASpartaProject_8Character>())
	{
		return;
	}

	OverlappedCharacters.AddUnique(OtherActor);

	if (DetectSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DetectSound, GetActorLocation());
	}

	if (!bExplosionStarted)
	{
		bExplosionStarted = true;
		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ABombItem::Explode, ExplosionDelay, false);
	}
}

void ABombItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappedCharacters.Remove(OtherActor);
}

void ABombItem::Explode()
{
	if (ExplosionEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, GetActorLocation(), GetActorRotation());
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, GetActorLocation());
	}

	TArray<AActor*> DamagedActors;
	Collision->GetOverlappingActors(DamagedActors, ASpartaProject_8Character::StaticClass());

	for (AActor* Actor : DamagedActors)
	{
		if (ASpartaProject_8Character* Character = Cast<ASpartaProject_8Character>(Actor))
		{
			Character->ApplyDamageToHP(Damage);
			if (ASpartaProject_8GameMode* GameMode = Cast<ASpartaProject_8GameMode>(UGameplayStatics::GetGameMode(this)))
			{
				GameMode->SetPlayerHP(Character->GetHP());
			}
		}
	}

	Destroy();
}
