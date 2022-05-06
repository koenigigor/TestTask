// Igor TestTask

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TTMovementComponent.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class TESTTASK_API UTTMovementComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UTTMovementComponent();

	virtual void BeginPlay() override;
	
	/** Set pawn movement velocity */
	UFUNCTION(BlueprintCallable)
	void SetVelocity(float NewVelocity);

	/** Client add movement from axis event by this */
	UFUNCTION(BlueprintCallable)
	void AddMovementInput(float Value);

private:
	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSetVelocity(float NewVelocity);

	UFUNCTION(NetMulticast, Unreliable)
	void SetVelocity_Internal(float NewVelocity);

	
	/** return result velocity in frame */
	void CalcThrottle(float DeltaTime);
	
	void ExecMovement();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** find left and right movement constraints
	 *	for move within the screen */
	void FindMovementConstraint();
	
private:
	UPROPERTY(Replicated)
	float Velocity = 0.f;

	//velocity on previous frame
	float PreviousVelocity = 0.f;

	float Throttle = 0.f;

	//keep previous movement input for determine is speed setup by AddMovementInput or by SetVelocity
	float PreviousMovementInput = 0.f;

public:
	/* left and right movement constraint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite) //temp
	FVector2D MovementConstraints;
};
