// Sakurasaki All Rights Reserved.


#include "Controllers/WeaverPlayerController.h"

AWeaverPlayerController::AWeaverPlayerController()
{
	PlayerTeamID = FGenericTeamId(0);
}

FGenericTeamId AWeaverPlayerController::GetGenericTeamId() const
{
	return PlayerTeamID;
}
