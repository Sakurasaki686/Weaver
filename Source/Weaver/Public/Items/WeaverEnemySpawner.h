// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaverEnemySpawner.generated.h"

class AWeaverEnemyCharacter;
class UNiagaraComponent;
class UBoxComponent;

UCLASS()
class WEAVER_API AWeaverEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaverEnemySpawner();

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings")
	TSubclassOf<AWeaverEnemyCharacter> EnemyClassToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings", meta = (ClampMin = "1"))
	int32 NumberOfEnemiesToSpawn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner Settings", meta = (ClampMin = "0.0"))
	float SpawnRadius = 500.f;
};
