// Igor TestTask


#include "TTMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void UTTMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTTMovementComponent, Velocity);
}

UTTMovementComponent::UTTMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	SetIsReplicatedByDefault(true);

	MovementConstraints = FVector2D(-99999, 99999);
}

void UTTMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	FindMovementConstraint();
}


void UTTMovementComponent::SetVelocity(float NewVelocity)
{
	if (GetOwnerRole() == ROLE_Authority)	
		SetVelocity_Internal(NewVelocity);

	if (GetOwnerRole() == ROLE_AutonomousProxy)
		ServerSetVelocity(NewVelocity);
}

void UTTMovementComponent::ServerSetVelocity_Implementation(float NewVelocity)
{
	SetVelocity(NewVelocity);
}

bool UTTMovementComponent::ServerSetVelocity_Validate(float NewVelocity)
{
	return true;
}

void UTTMovementComponent::SetVelocity_Internal_Implementation(float NewVelocity)
{
	Velocity = NewVelocity;
}


void UTTMovementComponent::CalcThrottle(float DeltaTime)
{
	if (FMath::IsNearlyEqual(Velocity, 0.f))
	{
		Throttle = 0.f;
		return;
	}
	
	Throttle = Velocity * DeltaTime;

	//clamp throttle
	const auto CurrentLocation = GetOwner()->GetActorLocation().X;
	auto NewLocation = CurrentLocation + Throttle;
	NewLocation = FMath::Clamp(NewLocation, MovementConstraints.X, MovementConstraints.Y);

	Throttle = NewLocation - CurrentLocation;
}

void UTTMovementComponent::ExecMovement()
{
	if (FMath::IsNearlyEqual(Throttle, 0.f)) return;

	const auto Offset = FVector(Throttle, 0.f, 0.f);
	GetOwner()->AddActorLocalOffset(Offset);
}

void UTTMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalcThrottle(DeltaTime);
	ExecMovement();
}

void UTTMovementComponent::FindMovementConstraint()
{
	//TODO
	//GetWorld()->GetFirstPlayerController()->DeprojectScreenPositionToWorld(0, 0, LeftLocation, WorldDirection);
	
	MovementConstraints = FVector2D(-600.f, 600.f);
}
