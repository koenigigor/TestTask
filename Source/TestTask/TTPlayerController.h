// Igor TestTask

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTTASK_API ATTPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void AcknowledgePossession(APawn* P) override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_AcknowledgePossession(APawn* NewPawn);
};
