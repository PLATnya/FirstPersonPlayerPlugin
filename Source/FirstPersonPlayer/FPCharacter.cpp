// 


#include "FPCharacter.h"

#include "Components/FPCharacterMovementComponent.h"

/*AFPCharacter::AFPCharacter(const FObjectInitializer& _ObjectInitializer)
	:Super(_ObjectInitializer.SetDefaultSubobjectClass<UFPCharacterMovementComponent>(CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}*/


void AFPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward/Backwards", this, &AFPCharacter::OnForwardMove);
	PlayerInputComponent->BindAxis("MoveRight/Left", this, &AFPCharacter::OnRightMove);

	PlayerInputComponent->BindAction("JumpAction", EInputEvent::IE_Pressed, this, &ACharacter::Jump);
}

void AFPCharacter::OnForwardMove(float _AxisValue)
{

	AddMovementInput(GetActorForwardVector() * _AxisValue);
}

void AFPCharacter::OnRightMove(float _AxisValue)
{
	AddMovementInput(GetActorRightVector() * _AxisValue);
}