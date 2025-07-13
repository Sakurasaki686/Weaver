// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WeaverCharacterAnimInstance.h"
#include "WeaverPlayerAnimInstance.generated.h"

class AWeaverPlayerCharacter;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverPlayerAnimInstance : public UWeaverCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="AnimData|References")
	AWeaverPlayerCharacter* OwningPlayerCharacter;
};
