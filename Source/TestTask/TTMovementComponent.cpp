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

	SetComponentTickEnabled(false);

	FindMovementConstraint();
}


void UTTMovementComponent::SetVelocity(float NewVelocity)
{
	//if (FMath::IsNearlyEqual(Velocity, NewVelocity) && FMath::IsNearlyEqual(PreviousVelocity, Velocity)) return;

	if (FMath::IsNearlyEqual(Velocity, NewVelocity)) return;
	
	if (GetOwnerRole() == ROLE_Authority)	
		SetVelocity_Internal(NewVelocity);

	if (GetOwnerRole() == ROLE_AutonomousProxy)
		ServerSetVelocity(NewVelocity);
}

void UTTMovementComponent::AddMovementInput(float Value)
{
	//ignore input if is 0, also check previous for determine if we moved directly by SetVelocity
	if (FMath::IsNearlyEqual(Value, 0.f) && FMath::IsNearlyEqual(PreviousMovementInput, Value)) return;
	PreviousMovementInput = Value;

	
	//calculate velocity from input, and set is as velocity
	float IntendedVelocity = Value * 50.f;
	IntendedVelocity = FMath::RoundHalfToEven(IntendedVelocity);


	SetVelocity(IntendedVelocity);
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
	if (FMath::IsNearlyEqual(NewVelocity, 0.f))
	{
		//stop movement
		SetComponentTickEnabled(false);
		UE_LOG(LogTemp, Display, TEXT("Pawn %s, Stop Movement"), *GetOwner()->GetName())
	}
	else
	{
		//start movement if stopped
		if (!IsComponentTickEnabled())
		{
			SetComponentTickEnabled(true);
			UE_LOG(LogTemp, Display, TEXT("Pawn %s, Start Movement"), *GetOwner()->GetName())
		}
	}
	
	VelocityChangeMessage();

	PreviousVelocity = Velocity;
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

void UTTMovementComponent::VelocityChangeMessage() const
{
	//UE_LOG(LogTemp, Display, TEXT("Movement velocity changed, old velocity is %f, new velocity is %f"), PreviousVelocity, Velocity)

	if (GetOwnerRole() == ROLE_Authority)
	{
		FString Message = "Movement velocity changed, old velocity is " + FString::SanitizeFloat(PreviousVelocity) + ", new velocity is " + FString::SanitizeFloat(Velocity);
		UKismetSystemLibrary::PrintString(this, Message, true, true, FLinearColor::Green, 5);
	}
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
