// Sakurasaki All Rights Reserved.


#include "Items/WeaverEnemySpawnerBase.h"

#include "NavigationSystem.h"
#include "NiagaraComponent.h"
#include "Characters/WeaverEnemyCharacter.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AWeaverEnemySpawnerBase::AWeaverEnemySpawnerBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerVolume"));
	TriggerVolume->SetupAttachment(RootComponent);
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerVolume->bHiddenInGame = true;

	VisualEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("VisualEffect"));
	VisualEffect->SetupAttachment(RootComponent);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
}

void AWeaverEnemySpawnerBase::BeginPlay()
{
	Super::BeginPlay();

	if (LoopingSound)
	{
		AudioComponent->SetSound(LoopingSound);
		AudioComponent->FadeIn(2.f, 1.f, 0.f);
	}

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

	VisualEffect->OnSystemFinished.AddDynamic(this, &ThisClass::OnEffectFinished);
}

void AWeaverEnemySpawnerBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AWeaverPlayerCharacter>(OtherActor))
	{
		TriggerAndFadeOut(OtherActor);
	}
}

void AWeaverEnemySpawnerBase::OnEffectFinished(UNiagaraComponent* PSystem)
{
	Destroy();
}

void AWeaverEnemySpawnerBase::SpawnEnemies(AActor* InInstigator)
{
	if (!EnemyClassToSpawn || !InInstigator)
	{
		UE_LOG(LogTemp, Warning, TEXT("AWeaverEnemySpawner: EnemyClassToSpawn or InInstigator is not set!"));
		return;
	}

	UWorld* World = GetWorld();
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
	
	if (!World || !NavSys) return;
	
	const FVector SpawnerLocation = GetActorLocation();
	int NumberOfEnemiesToSpawn = FMath::RandRange(MinSpawnAmount, MaxSpawnAmount);
	
	for (int32 i = 0; i < NumberOfEnemiesToSpawn; ++i)
	{
		FNavLocation RandomNavLocation;
		const bool bFoundPoint = NavSys->GetRandomPointInNavigableRadius(SpawnerLocation, SpawnRadius, RandomNavLocation);

		if (bFoundPoint)
		{
			const FVector SpawnLocation = RandomNavLocation.Location;

			FVector Direction3D = InInstigator->GetActorLocation() - SpawnLocation;
			FVector Direction2D = FVector(Direction3D.X, Direction3D.Y, 0.f).GetSafeNormal();
			const FRotator SpawnRotation = Direction2D.Rotation();

			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			
			AWeaverEnemyCharacter* NewSpawnedEnemy = World->SpawnActor<AWeaverEnemyCharacter>(EnemyClassToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			if (NewSpawnedEnemy)
			{
				OnEnemySpawned(NewSpawnedEnemy);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AWeaverEnemySpawner: Could not find a valid point on NavMesh within radius %f"), SpawnRadius);
		}
	}
}

void AWeaverEnemySpawnerBase::TriggerAndFadeOut(AActor* InInstigator)
{
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpawnEnemies(InInstigator);
	
	if (VisualEffect)
	{
		VisualEffect->Deactivate();
	}

	if (AudioComponent->IsPlaying())
	{
		AudioComponent->FadeOut(2.f, 0.f);
	}
}
