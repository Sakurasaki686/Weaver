// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UWeaverWidgetBase;
/**
 * 
 */
UCLASS()
class WEAVER_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UWeaverWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UWeaverWidgetBase*> EnemyDrawnWidgets;
};
