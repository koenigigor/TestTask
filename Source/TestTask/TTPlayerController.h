// Igor TestTask

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TTPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAcknowledgePossessionDelegate, APawn*, InPawn);
//todo as remember delegate crush if send nullptr? check

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

	UPROPERTY(BlueprintAssignable)
	FAcknowledgePossessionDelegate OnPossessClient;
};
