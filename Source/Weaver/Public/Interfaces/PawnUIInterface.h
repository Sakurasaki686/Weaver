// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

class UPawnUIComponent;
class UPlayerUIComponent;
class UEnemyUIComponent;

UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WEAVER_API IPawnUIInterface
{
	GENERATED_BODY()

public:
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;
	
	virtual UPlayerUIComponent* GetPlayerUIComponent() const;

	virtual UEnemyUIComponent* GetEnemyUIComponent() const;
};
