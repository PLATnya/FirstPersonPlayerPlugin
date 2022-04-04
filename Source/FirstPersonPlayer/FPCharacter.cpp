// 


#include "FPCharacter.h"


// Sets default values
AFPCharacter::AFPCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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
}

void AFPCharacter::OnRightMove(float _AxisValue)
{
	AddMovementInput(GetActorRightVector() * _AxisValue);
}


