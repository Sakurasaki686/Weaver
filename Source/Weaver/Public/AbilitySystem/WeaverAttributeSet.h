// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "WeaverAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UWeaverAttributeSet();
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData &Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UWeaverAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UWeaverAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData AttackMultiplier;
	ATTRIBUTE_ACCESSORS(UWeaverAttributeSet, AttackMultiplier)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UWeaverAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UWeaverAttributeSet, DamageTaken)
};
