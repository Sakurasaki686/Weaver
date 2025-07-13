// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "WeaverBaseCharacter.generated.h"

class UDataAsset_StartUpDataBase;
class UWeaverAttributeSet;
class UWeaverAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS()
class WEAVER_API AWeaverBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	AWeaverBaseCharacter();

	//~ Begin IAbilitySystemInterface Interface.
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~ End IAbilitySystemInterface Interface

	//~ Begin IPawnCombatInterface Interface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface Interface

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	EWeaverCharacterGait CharacterDefaultGait = EWeaverCharacterGait::Run;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	float MaxRunSpeed = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	float MaxWalSpeed = 200.f;

protected:
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	//~ Begin ACharacter Interface.
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	//~ End ACharacter Interface
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWeaverAbilitySystemComponent* WeaverAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWeaverAttributeSet* WeaverAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

public:
	FORCEINLINE UWeaverAbilitySystemComponent* GetWeaverAbilitySystemComponent() const { return WeaverAbilitySystemComponent; }
	FORCEINLINE UWeaverAttributeSet* GetWeaverAttributeSet() const { return WeaverAttributeSet; }
};
