// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectileExtensionComponentBase.generated.h"


class AWeaverProjectileBase;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAVER_API UProjectileExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	UProjectileExtensionComponentBase();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Effect")
	TObjectPtr<AWeaverProjectileBase> OwningProjectile;
	
	UFUNCTION(BlueprintNativeEvent, Category = "Effect|Events")
	void OnOwnerProjectileSpawn();

	UFUNCTION(BlueprintNativeEvent, Category = "Effect|Events")
	void OnOwnerProjectileOverlap(AActor* OverlappedActor);

	UFUNCTION(BlueprintNativeEvent, Category = "Effect|Events")
	void OnOwnerProjectileHit(AActor* HitActor, const FHitResult& HitResult);

	UFUNCTION(BlueprintNativeEvent, Category = "Effect|Events")
	void OnOwnerProjectileDestroy();
};
