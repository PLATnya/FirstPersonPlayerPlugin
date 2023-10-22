// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

class UFPLadderMovementComponent;
class UFPClimbingComponent;
class UFPAdvancedMovementComponent;

UCLASS()
class FIRSTPERSONPLAYER_API AFPCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AFPCharacter();

	UFPAdvancedMovementComponent* GetAdvancedMovement() { return AdvancedMovementComponent; }

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UFPClimbingComponent* GetClimbingComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UFPLadderMovementComponent* GetLadderMoveComponent();
protected:

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UFPAdvancedMovementComponent* AdvancedMovementComponent;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnForwardMove(float _AxisValue);
	virtual void OnRightMove(float _AxisValue);

	virtual void OnJumpPressed();
};