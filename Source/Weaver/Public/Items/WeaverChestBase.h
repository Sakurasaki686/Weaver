// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/PawnInteractionInterface.h"
#include "WeaverChestBase.generated.h"

class UBoxComponent;

UCLASS()
class WEAVER_API AWeaverChestBase : public AActor, public IPawnInteractionInterface
{
	GENERATED_BODY()
	
public:	
	AWeaverChestBase();

	virtual void BeginPlay() override;

	//~ Begin IPawnInteractionInterface Interface
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
	//~ End IPawnInteractionInterface Interface

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Weaver|Chest")
	void Open();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> ChestMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration|Effects", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> OpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration|Animation", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAnimationAsset> OpenAnimation;
};
