// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPPlayerController.generated.h"

UCLASS()
class FIRSTPERSONPLAYER_API AFPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPPlayerController();

	virtual void SetupInputComponent() override;

	virtual void OnTurnUp(float _AxisValue);
	virtual void OnTurnRight(float _AxisValue);
};