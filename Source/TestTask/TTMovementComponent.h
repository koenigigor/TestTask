// Igor TestTask

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "TTMovementComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TESTTASK_API UTTMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
public:
	UTTMovementComponent();
	
	/** Set pawn movement velocity */
	UFUNCTION(BlueprintCallable)
	void SetVelocity(float NewVelocity);

	/** return result velocity in frame */
	float CalcThrottle(float DeltaTime);
	
	void ExecMovement(float Throttle);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** execute on postregistercomponent
	 *	find left and right movement constraints */
	void FindMovementConstraint();
	
private:
	float Velocity = 0.f;

public:
	/* left and right movement constraint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) //temp
	FVector2D MovementConstraints;
};
