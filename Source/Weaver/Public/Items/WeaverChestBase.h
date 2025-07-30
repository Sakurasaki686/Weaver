// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PawnInteractionInterface.h"
#include "WeaverChestBase.generated.h"

class UWeaverRewardComponent;
class UBoxComponent;

UCLASS()
class WEAVER_API AWeaverChestBase : public AActor, public IPawnInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AWeaverChestBase();

	virtual void BeginPlay() override;

	//~ Begin IPawnInteractionInterface Interface
	virtual void Interact_Implementation(AActor* InInstigator) override;
	//~ End IPawnInteractionInterface Interface

	UFUNCTION(BlueprintPure, Category = "Weaver|Chest")
	bool CanOpen(AActor* InInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Weaver|Chest")
	void Open(AActor* InInstigator);

protected:
	UFUNCTION()
	void OnInteractionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|Chest")
	void StartRewardSelection();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Cost")
	float AetherCostToOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Interaction")
	FText ChestInteractionHint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuration|Interaction")
	FText ChestInteractionWarningHint;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionBox;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ChestMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWeaverRewardComponent> RewardComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration|Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimationAsset> OpenAnimation;
};
