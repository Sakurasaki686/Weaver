// Sakurasaki All Rights Reserved.


#include "WeaverFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "WeaverGameInstance.h" 
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

UWeaverAbilitySystemComponent* UWeaverFunctionLibrary::NativeGetWeaverASCFromActor(AActor* InActor)
{
	check(InActor);

	return CastChecked<UWeaverAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));

}

void UWeaverFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UWeaverAbilitySystemComponent* ASC = NativeGetWeaverASCFromActor(InActor);

	if (!ASC || !TagToAdd.IsValid())
	{
		return;
	}

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWeaverFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UWeaverAbilitySystemComponent* ASC = NativeGetWeaverASCFromActor(InActor);

	if (!ASC || !TagToRemove.IsValid())
	{
		return;
	}

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

void UWeaverFunctionLibrary::AddGameplayTagsToActorIfNone(AActor* InActor, FGameplayTagContainer TagsToAdd)
{
	for (const FGameplayTag& Tag : TagsToAdd)
	{
		AddGameplayTagToActorIfNone(InActor, Tag);
	}
}

void UWeaverFunctionLibrary::RemoveGameplayTagsFromActorIfFound(AActor* InActor, FGameplayTagContainer TagsToRemove)
{
	for (const FGameplayTag& Tag : TagsToRemove)
	{
		RemoveGameplayTagFromActorIfFound(InActor, Tag);
	}
}

bool UWeaverFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UWeaverAbilitySystemComponent* ASC = NativeGetWeaverASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UWeaverFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWeaverConfirmType& OutConfirmType)
{
	NativeDoesActorHaveTag(InActor, TagToCheck) ? OutConfirmType = EWeaverConfirmType::Yes : OutConfirmType = EWeaverConfirmType::No;
}

UPawnCombatComponent* UWeaverFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWeaverFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWeaverValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	
	OutValidType = CombatComponent ? EWeaverValidType::Valid : EWeaverValidType::Invalid;
	
	return CombatComponent;
}

bool UWeaverFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UWeaverFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UWeaverFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return WeaverGameplayTags::Shared_Status_HitReact_Front;
	}
	if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return WeaverGameplayTags::Shared_Status_HitReact_Right;
	}
	if (OutAngleDifference > 135.f || OutAngleDifference < -135.f)
	{
		return WeaverGameplayTags::Shared_Status_HitReact_Back;
	}
	if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return WeaverGameplayTags::Shared_Status_HitReact_Left;
	}

	return WeaverGameplayTags::Shared_Status_HitReact_Front;
}

bool UWeaverFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	return false;
}

bool UWeaverFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UWeaverAbilitySystemComponent* SourceASC = NativeGetWeaverASCFromActor(InInstigator);
	UWeaverAbilitySystemComponent* TargetASC = NativeGetWeaverASCFromActor(InTargetActor);

	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InSpecHandle.Data, TargetASC);

	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UWeaverFunctionLibrary::Countdown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime, EWeaverCountdownActionInput CountdownInput, EWeaverCountdownActionOutput& CountdownOutput, FLatentActionInfo LatentInfo)
{
	// UWorld* World = nullptr;
	//
	// if (GEngine)
	// {
	// 	World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	// }
	//
	// if (!World)
	// {
	// 	return;
	// }
	//
	// FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	//
	// FWeaverCountdownAction* FoundAction = LatentActionManager.FindExistingAction<FWeaverCountdownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	//
	// if (CountdownInput == EWeaverCountdownActionInput::Start)
	// {
	// 	if (!FoundAction)
	// 	{
	// 		LatentActionManager.AddNewAction(
	// 			LatentInfo.CallbackTarget,
	// 			LatentInfo.UUID,
	// 			new FWeaverCountdownAction(TotalTime, UpdateInterval, OutRemainingTime, CountdownOutput, LatentInfo)
	// 		);
	// 	}
	// }
	//
	// if (CountdownInput == EWeaverCountdownActionInput::Cancel)
	// {
	// 	if (FoundAction)
	// 	{
	// 		FoundAction->CancelAction();
	// 	}
	// }
}

UWeaverGameInstance* UWeaverFunctionLibrary::GetWeaverGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UWeaverGameInstance>();
		}
	}

	return nullptr;
}

void UWeaverFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EWeaverInputMode InInputMode)
{
	APlayerController* PlayerController = nullptr;

	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}

	if (!PlayerController)
	{
		return;
	}

	FInputModeGameOnly GameOnlyMode;
	FInputModeUIOnly UIOnlyMode;

	switch (InInputMode)
	{
	case EWeaverInputMode::GameOnly:
		{
			PlayerController->SetInputMode(GameOnlyMode);
			PlayerController->bShowMouseCursor = false;
			break;
		}
	case EWeaverInputMode::UIOnly:
		{
			PlayerController->SetInputMode(UIOnlyMode);
			PlayerController->bShowMouseCursor = true;
			break;
		}
	default:
		break;
	}
}
