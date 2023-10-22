// 


#include "FPCharacter.h"

#include "Components/FPAdvancedMovementComponent.h"
#include "Components/FPClimbingComponent.h"
#include "Components/FPLadderMovementComponent.h"


AFPCharacter::AFPCharacter()
{
	AdvancedMovementComponent = CreateDefaultSubobject<UFPAdvancedMovementComponent>("Advanced Movement");
}

UFPClimbingComponent* AFPCharacter::GetClimbingComponent_Implementation()
{
	return nullptr;
}

UFPLadderMovementComponent* AFPCharacter::GetLadderMoveComponent_Implementation()
{
	return nullptr;
}

void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward/Backwards", this, &AFPCharacter::OnForwardMove);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &AFPCharacter::OnRightMove);
	PlayerInputComponent->BindAction("JumpAction", IE_Pressed, this, &AFPCharacter::OnJumpPressed);
}

void AFPCharacter::OnForwardMove(float _AxisValue)
{
	AddMovementInput(GetActorForwardVector() * _AxisValue);
	UFPClimbingComponent* ClimbingComponent = GetClimbingComponent();
	if (IsValid(ClimbingComponent))
	{
		ClimbingComponent->ClimbVertical(_AxisValue);	
	}

	UFPLadderMovementComponent* LadderMovementComponent = GetLadderMoveComponent();
	if (IsValid(LadderMovementComponent))
	{
		LadderMovementComponent->ClimbVertical(_AxisValue);
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

void AFPCharacter::OnJumpPressed()
{
 	GetClimbingComponent()->JumpFromClimb();
	GetLadderMoveComponent()->JumpFromClimb();
	Jump();
}
