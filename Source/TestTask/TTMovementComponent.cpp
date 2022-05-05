// Igor TestTask


#include "TTMovementComponent.h"

UTTMovementComponent::UTTMovementComponent()
{
	//tick
}

void UTTMovementComponent::SetVelocity(float NewVelocity)
{
	Velocity = NewVelocity;
}

void UTTMovementComponent::CalcThrottle(float DeltaTime)
{
	if (FMath::IsNearlyEqual(Velocity, 0.f)) return;
	
	Throttle = Velocity * DeltaTime;
}

void UTTMovementComponent::ExecMovement()
{
	if (FMath::IsNearlyEqual(Throttle, 0)) return;

	const auto Offset = FVector(Throttle, 0, 0);
	GetOwner()->AddActorLocalOffset(Offset);
}

void UTTMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalcThrottle(Throttle);
	ExecMovement();
}

void UTTMovementComponent::FindMovementConstraint()
{
	//TODO
	//get players screen 

	//get right edge

	//get left edge

	
	//how get on server
	//calculate on client and send to server?
}
