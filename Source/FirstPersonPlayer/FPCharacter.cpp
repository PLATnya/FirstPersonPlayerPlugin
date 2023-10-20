// 


#include "FPCharacter.h"

#include "Components/FPAdvancedMovementComponent.h"
#include "Components/FPClimbingComponent.h"


AFPCharacter::AFPCharacter()
{
	AdvancedMovementComponent = CreateDefaultSubobject<UFPAdvancedMovementComponent>("Advanced Movement");
	//ClimbingComponent = CreateDefaultSubobject<UFPClimbingComponent>("Climbing Component");
}

UFPClimbingComponent* AFPCharacter::GetClimbingComponent_Implementation()
{
	return nullptr;
}

void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward/Backwards", this, &AFPCharacter::OnForwardMove);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &AFPCharacter::OnRightMove);
	
}

void AFPCharacter::OnForwardMove(float _AxisValue)
{
	AddMovementInput(GetActorForwardVector() * _AxisValue);
	UFPClimbingComponent* ClimbingComponent = GetClimbingComponent();
	if (IsValid(ClimbingComponent))
	{
		ClimbingComponent->ClimbVertical(_AxisValue);	
	}
}

void AFPCharacter::OnRightMove(float _AxisValue)
{
	AddMovementInput(GetActorRightVector() * _AxisValue);
	UFPClimbingComponent* ClimbingComponent = GetClimbingComponent();
	if (IsValid(ClimbingComponent))
	{
		ClimbingComponent->ClimbHorizontal(_AxisValue);	
	}
}