// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Interfaces/PawnUIInterface.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "WeaverBaseCharacter.generated.h"

#define ECC_PlayerSpellProjectile ECC_GameTraceChannel3
#define ECC_EnemySpellProjectile ECC_GameTraceChannel4

struct FOnAttributeChangeData;
class UDataAsset_StartUpDataBase;
class UWeaverAttributeSet;
class UWeaverAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS()
class WEAVER_API AWeaverBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
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
	
	//~ Begin IPawnUIInterface Interface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//~ End IPawnUIInterface Interface

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Locomotion")
	EWeaverCharacterGait CharacterDefaultGait = EWeaverCharacterGait::Run;

protected:
	virtual void BeginPlay() override;
	
	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	//~ Begin ACharacter Interface.
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;
	//~ End ACharacter Interface

	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	
	void OnMovementAttributesChanged(const FOnAttributeChangeData& Data);
	
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

protected:
	EWeaverCharacterGait CurrentGait;
};
