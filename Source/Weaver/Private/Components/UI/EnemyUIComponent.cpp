// Sakurasaki All Rights Reserved.


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/WeaverWidgetBase.h"

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UWeaverWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
	if (EnemyDrawnWidgets.IsEmpty())
	{
		return;
	}

	for (UWeaverWidgetBase* DrawnWidget : EnemyDrawnWidgets)
	{
		if (DrawnWidget)
		{
			DrawnWidget->RemoveFromParent();
		}
	}

	EnemyDrawnWidgets.Empty();
}
