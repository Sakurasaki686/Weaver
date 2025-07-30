// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WeaverTypes/WeaverStructTypes.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class UDataAsset_TunerBase;
class UDataAsset_AffixBase;
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
	UPlayerCombatComponent();
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	AWeaverPlayerWeapon* GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	AWeaverPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Weaver|Combat")
	float GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const;

	virtual void OnHitTargetActor(AActor* HitActor) override;
	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weaver|Spell Alchemist", meta = (AllowPrivateAccess = "true"))
	TMap<FGameplayTag, FAffixCategory> CategorizedAffixes;

public:
	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_TunerBase* GetSelectedTuner() const;

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	FGameplayTag GetSelectedTunerTag() const;

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_ElementBase* GetSelectedElement() const;

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_EffectBase* GetSelectedEffect() const;

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedTuner(UDataAsset_TunerBase* InTuner);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedElement(UDataAsset_ElementBase* InElement);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedEffect(UDataAsset_EffectBase* InEffect);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void AddAffix(UDataAsset_AffixBase* InAffixData);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void AddAndSetTuner(UDataAsset_TunerBase* InTuner);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void AddAndSetElement(UDataAsset_ElementBase* InElement);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void AddAndSetEffect(UDataAsset_EffectBase* InEffect);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	UDataAsset_AffixBase* SwitchToNextAffixInCurrentCategory(FGameplayTag InCategoryTag);
};
