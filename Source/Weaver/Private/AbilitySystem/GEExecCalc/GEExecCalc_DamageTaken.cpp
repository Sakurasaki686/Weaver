// Sakurasaki All Rights Reserved.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAttributeSet.h"

struct FWeaverDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackMultiplier);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FWeaverDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWeaverAttributeSet, AttackMultiplier, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWeaverAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWeaverAttributeSet, DamageTaken, Target, false);
	}
};

static const FWeaverDamageCapture& GetWeaverDamageCapture()
{
	static FWeaverDamageCapture WeaverDamageCapture;
	return WeaverDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	RelevantAttributesToCapture.Add(GetWeaverDamageCapture().AttackMultiplierDef);
	RelevantAttributesToCapture.Add(GetWeaverDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetWeaverDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float AttackMultiplier = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWeaverDamageCapture().AttackMultiplierDef, EvaluateParameters, AttackMultiplier);

	float TargetDefensePower = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWeaverDamageCapture().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	float BaseDamage = 0.f;

	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(WeaverGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
		}
	}

	float FinalDamageDone = BaseDamage * AttackMultiplier / TargetDefensePower;
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetWeaverDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone
			)
		);
	}
}
