// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WeaverBaseAnimInstance.h"
#include "WeaverCharacterAnimInstance.generated.h"

class AWeaverBaseCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverCharacterAnimInstance : public UWeaverBaseAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	AWeaverBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	float LocomotionDirection;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|LocomotionData")
	bool IsInAir;
};
