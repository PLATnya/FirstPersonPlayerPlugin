// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"



UCLASS()
class FIRSTPERSONPLAYER_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	//AFPCharacter( const FObjectInitializer& _ObjectInitializer);

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;



	virtual void OnForwardMove(float _AxisValue);
	virtual void OnRightMove(float _AxisValue);

};