// Igor TestTask


#include "TTPlayerController.h"

void ATTPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	BP_AcknowledgePossession(P);
}
