// 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPAdvancedMovementComponent.generated.h"

struct FTimeline;
class UCharacterMovementComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONPLAYER_API UFPAdvancedMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFPAdvancedMovementComponent(const FObjectInitializer& ObjectInitializer);

	void StartSprinting();
	void StopSprinting();

	void StartCrouch();
	void UpdateCrouching(float DeltaTime);
	void StopCrouch();
	
protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginPlay() override;


private:

	UFUNCTION()
	class AFPCharacter* GetCharacterOwner() const;

	UFUNCTION()
	UCharacterMovementComponent* GetCharacterMovement() const;

	UFUNCTION()
	UCapsuleComponent* GetCharacterCapsule() const;

	UPROPERTY(Transient)
	float BuffMaxWalkSpeed = 0.0f;

	UPROPERTY(EditAnywhere, Category="Running")
	float RunSpeed = 600.0f;

	UPROPERTY(VisibleAnywhere, Category="Running")
	bool bIsSprinting = false;
	
	UPROPERTY(Transient)
	float BuffHalfHeight = 0.0f;
	
	UPROPERTY(Transient)
	float CrouchSmoothTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Crouching")
	float CrouchSmoothMaxTime = 1.0f;

	UPROPERTY(VisibleAnywhere, Category="Crouching")
	bool bIsCrouching = false;


};