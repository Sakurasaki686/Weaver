// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaverPickupItemsBase.generated.h"

class UAudioComponent;
class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class WEAVER_API AWeaverPickupItemsBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaverPickupItemsBase();

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|PickupItem")
	void OnInteractionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|PickupItem")
	void OnInteractionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickupItem")
	TObjectPtr<UBoxComponent> InteractionBox;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "PickupItem")
	TObjectPtr<UNiagaraComponent> AetherNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Audio")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Audio")
	TObjectPtr<USoundBase> LoopingSound;
};
