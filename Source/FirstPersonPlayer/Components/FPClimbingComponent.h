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

	EFPClimbingState GetCurrentClimbingState() const { return CurrentState; }
	UFUNCTION(BlueprintCallable)
	bool TryClimb(UPrimitiveComponent* ClimbingComponent);

	void ClimbHorizontal(float AxisFactor);
	void ClimbVertical(float AxisFactor);
		
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	void ClimbInDirection(FVector Direction);
	FVector GetClimbingPoint(UPrimitiveComponent* ClimbingOnComponent, const FVector& Location, const FVector& LocationNormal) const;
	UFUNCTION(BlueprintCallable)
	FVector GetPointOnEdge(UPrimitiveComponent* ClimbingOnComponent, const FVector Location) const;
	class AFPCharacter* GetOwnedCharacter() const;

	EFPClimbingState CurrentState = EFPClimbingState::None;

	bool bIsClimbing = false;
	FVector ClimbingPoint = FVector::ZeroVector;
	
	UPROPERTY()
	UPrimitiveComponent* LastClimbComponent = nullptr;
};