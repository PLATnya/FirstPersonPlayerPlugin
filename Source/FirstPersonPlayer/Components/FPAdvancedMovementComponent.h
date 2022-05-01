// 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPAdvancedMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONPLAYER_API UFPAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFPAdvancedMovementComponent(const FObjectInitializer& ObjectInitializer);

	void StartSprinting();

	void StopSprinting();

protected:


private:

	UFUNCTION()
	class AFPCharacter* GetCharacterOwner() const;

	UFUNCTION()
	class UCharacterMovementComponent* GetCharacterMovement() const;

	UPROPERTY(Transient)
	float BuffMaxWalkSpeed = 0.0f;


	UPROPERTY(EditAnywhere, Category="Running")
	float RunSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, Category="Running")
	bool bIsSprinting = false;


};