// 


#include "FPPlayerController.h"


// Sets default values
AFPPlayerController::AFPPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AFPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("LookUp/Down", this, &AFPPlayerController::OnTurnUp);
	InputComponent->BindAxis("LookLeft/Right", this, &AFPPlayerController::OnTurnRight);
}


void AFPPlayerController::OnTurnUp(float _AxisValue)
{
	AddPitchInput(_AxisValue);
}

void AFPPlayerController::OnTurnRight(float _AxisValue)
{
	AddYawInput(_AxisValue);
}