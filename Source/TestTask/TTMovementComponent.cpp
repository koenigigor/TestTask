// Igor TestTask


#include "TTMovementComponent.h"

#include "Kismet/GameplayStatics.h"

UTTMovementComponent::UTTMovementComponent()
{
	//tick
}

void UTTMovementComponent::SetVelocity(float NewVelocity)
{
	Velocity = NewVelocity;
}

float UTTMovementComponent::CalcThrottle(float DeltaTime)
{
	float Throttle = 0.f;

	if (FMath::IsNearlyEqual(Velocity, 0.f)) return Throttle;
	
	Throttle = Velocity * DeltaTime;

	//clamp throttle
	const auto CurrentLocation = GetOwner()->GetActorLocation().X;
	auto NewLocation = CurrentLocation + Throttle;
	NewLocation = FMath::Clamp(NewLocation, MovementConstraints.X, MovementConstraints.Y);

	Throttle = CurrentLocation - NewLocation;

	return Throttle;
}

void UTTMovementComponent::ExecMovement(float Throttle)
{
	if (FMath::IsNearlyEqual(Throttle, 0)) return;

	const auto Offset = FVector(Throttle, 0, 0);
	GetOwner()->AddActorLocalOffset(Offset);
}

void UTTMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto Throttle = CalcThrottle(DeltaTime);
	ExecMovement(Throttle);
}

void UTTMovementComponent::FindMovementConstraint()
{
	//TODO
	//GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(0, 0, LeftLocation, WorldDirection);
	
	
	//how get on server
	//calculate on client and send to server?
}
