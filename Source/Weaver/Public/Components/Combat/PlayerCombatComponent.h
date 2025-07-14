// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class UDataAsset_EffectBase;
class UDataAsset_ElementBase;
class AWeaverPlayerWeapon;
class AWeaverWeaponBase;

/**
 * 
 */
UCLASS()
class WEAVER_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	AWeaverPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	AWeaverPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weaver|Spell Alchemist")
	FGameplayTag SelectedTunerTag;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weaver|Spell Alchemist")
	TObjectPtr<UDataAsset_ElementBase> SelectedElement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weaver|Spell Alchemist")
	TObjectPtr<UDataAsset_EffectBase> SelectedEffect;

public:
	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	FGameplayTag GetSelectedTunerTag() const { return SelectedTunerTag; }

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_ElementBase* GetSelectedElement() const { return SelectedElement; }

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_EffectBase* GetSelectedEffect() const { return SelectedEffect; }

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedTuner(const FGameplayTag& InTunerTag);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedElement(UDataAsset_ElementBase* InElement);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedEffect(UDataAsset_EffectBase* InEffect);
};
