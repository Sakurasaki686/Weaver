// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaverEnemySpawnerBase.generated.h"

class UAudioComponent;
class AWeaverEnemyCharacter;
class UNiagaraComponent;
class UBoxComponent;

UCLASS()
class WEAVER_API AWeaverEnemySpawnerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaverEnemySpawnerBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Spawner")
	void OnEnemySpawned(AWeaverEnemyCharacter* SpawnedEnemy);

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(UNiagaraComponent* PSystem);

	void SpawnEnemies(AActor* InInstigator);

	void TriggerAndFadeOut(AActor* InInstigator);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> TriggerVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> VisualEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UAudioComponent> AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FX")
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
	TSubclassOf<AWeaverEnemyCharacter> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings", meta = (ClampMin = "0"))
	int32 MinSpawnAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings", meta = (ClampMin = "0"))
	int32 MaxSpawnAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings", meta = (ClampMin = "0.0"))
	float SpawnRadius = 500.f;
};
