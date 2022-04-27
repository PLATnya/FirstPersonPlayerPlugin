//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPClimbingComponent.generated.h"

UENUM()
enum class EFPClimbingState : uint8
{
	None = 0,

	StartGrabbing,
	Climbing,
	GrabbingUp
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONPLAYER_API UFPClimbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPClimbingComponent();

	UPrimitiveComponent* GetGrabbedPrimitiveComp() const { return pPrimitiveGrabbedObstacle; }
	EFPClimbingState GetCurrentClimbingState() const { return CurrentState; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	EFPClimbingState CurrentState = EFPClimbingState::None;

	UPROPERTY()
	UPrimitiveComponent* pPrimitiveGrabbedObstacle = nullptr;
};