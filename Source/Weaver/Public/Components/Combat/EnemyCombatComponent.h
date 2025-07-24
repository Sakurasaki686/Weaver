// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"

class UDataAsset_EffectBase;
class UDataAsset_ElementBase;
/**
 * 
 */
UCLASS()
class WEAVER_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weaver|Spell Alchemist")
	TObjectPtr<UDataAsset_ElementBase> SelectedElement;

	UPROPERTY(VisibleAnywhere, Category = "Weaver|Spell Alchemist")
	TObjectPtr<UDataAsset_EffectBase> SelectedEffect;

public:
	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_ElementBase* GetSelectedElement() const { return SelectedElement; }

	UFUNCTION(BlueprintPure, Category = "Weaver|Spell Alchemist")
	UDataAsset_EffectBase* GetSelectedEffect() const { return SelectedEffect; }

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedElement(UDataAsset_ElementBase* InElement);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Spell Alchemist")
	void SetSelectedEffect(UDataAsset_EffectBase* InEffect);
};
