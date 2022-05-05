// Igor TestTask


#include "TTMovementComponent.h"

#include "Kismet/GameplayStatics.h"

UTTMovementComponent::UTTMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MovementConstraints = FVector2D(-99999, 99999);
}

void UTTMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	FindMovementConstraint();
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

	Throttle = NewLocation - CurrentLocation;

	return Throttle;
}

void UTTMovementComponent::ExecMovement(float Throttle)
{
	if (FMath::IsNearlyEqual(Throttle, 0.f)) return;

	const auto Offset = FVector(Throttle, 0.f, 0.f);
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
	
	MovementConstraints = FVector2D(-600.f, 600.f);
}
