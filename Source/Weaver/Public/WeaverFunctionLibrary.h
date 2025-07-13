// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "WeaverFunctionLibrary.generated.h"

class UWeaverGameInstance;
class UPawnCombatComponent;
class UWeaverAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UWeaverAbilitySystemComponent* NativeGetWeaverASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary")
	static void AddGameplayTagsToActorIfNone(AActor* InActor, FGameplayTagContainer TagsToAdd);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary")
	static void RemoveGameplayTagsFromActorIfFound(AActor* InActor, FGameplayTagContainer TagsToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWeaverConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWeaverValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Weaver|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Weaver|FunctionLibrary", meta = (CompactNodeTitle = "Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "Weaver|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Weaver|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary", meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo", ExpandEnumAsExecs = "CountdownInput|CountdownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void Countdown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EWeaverCountdownActionInput CountdownInput, UPARAM(DisplayName = "Output") EWeaverCountdownActionOutput& CountdownOutput, FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "Weaver|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UWeaverGameInstance* GetWeaverGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Weaver|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EWeaverInputMode InInputMode);
};
