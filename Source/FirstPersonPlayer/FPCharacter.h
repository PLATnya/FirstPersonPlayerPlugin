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
	
	// Sets default values for this character's properties
	AFPCharacter();
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;


private:
	virtual void OnForwardMove(float _AxisValue);
	virtual void OnRightMove(float _AxisValue);

};
