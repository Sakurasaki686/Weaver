// Sakurasaki All Rights Reserved.


#include "Items/WeaverEnemySpawner.h"

#include "NiagaraComponent.h"
#include "Characters/WeaverEnemyCharacter.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AWeaverEnemySpawner::AWeaverEnemySpawner()
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
}

void AWeaverEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);

	VisualEffect->OnSystemFinished.AddDynamic(this, &ThisClass::OnEffectFinished);
}

void AWeaverEnemySpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && Cast<AWeaverPlayerCharacter>(OtherActor))
	{
		TriggerAndFadeOut(OtherActor);
	}
}

void AWeaverEnemySpawner::OnEffectFinished(UNiagaraComponent* PSystem)
{
	Destroy();
}

void AWeaverEnemySpawner::SpawnEnemies(AActor* InInstigator)
{
	if (!EnemyClassToSpawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("AWeaverEnemySpawner: EnemyClassToSpawn is not set!"));
		return;
	}

	UWorld* World = GetWorld();
	if (!World) return;
	
	const FVector SpawnerLocation = GetActorLocation();
	
	for (int32 i = 0; i < NumberOfEnemiesToSpawn; ++i)
	{
		FVector RandomUnitVector = UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, FVector(1.f, 1.f, 0.f)).GetSafeNormal();
		FVector RandomLocation = SpawnerLocation + RandomUnitVector * FMath::RandRange(0.f, SpawnRadius);

		FVector Direction = InInstigator->GetActorLocation() - RandomLocation;
		Direction.Normalize();
		FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(Direction);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		AWeaverEnemyCharacter* NewSpawnedEnemy = World->SpawnActor<AWeaverEnemyCharacter>(EnemyClassToSpawn, RandomLocation, TargetRotation, SpawnParams);

		if (NewSpawnedEnemy)
		{
			OnEnemySpawned(NewSpawnedEnemy);
		}
	}
}

void AWeaverEnemySpawner::TriggerAndFadeOut(AActor* InInstigator)
{
	TriggerVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpawnEnemies(InInstigator);
	
	if (VisualEffect)
	{
		VisualEffect->Deactivate();
	}
}
