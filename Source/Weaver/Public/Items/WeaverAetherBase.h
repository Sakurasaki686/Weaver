// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaverAetherBase.generated.h"

class UAudioComponent;
class UBoxComponent;
class UNiagaraComponent;

UCLASS()
class WEAVER_API AWeaverAetherBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaverAetherBase();

	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|Aether")
	void OnInteractionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|Aether")
	void OnInteractionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aether")
	TObjectPtr<UBoxComponent> InteractionBox;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Aether")
	TObjectPtr<UNiagaraComponent> AetherNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Audio")
	TObjectPtr<USoundBase> PickupSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Audio")
	TObjectPtr<USoundBase> LoopingSound;
};
