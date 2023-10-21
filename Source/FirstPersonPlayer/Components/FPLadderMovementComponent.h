

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPLadderMovementComponent.generated.h"


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONPLAYER_API UFPLadderMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPLadderMovementComponent();
	UFUNCTION(BlueprintCallable)
	bool TryClimb(UPrimitiveComponent* LadderComponent);

	void ClimbVertical(float AxisFactor);
	class AFPCharacter* GetOwnedCharacter() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	FVector LadderOnLocation = FVector::ZeroVector;
	bool bOnLadder = false;

	UPROPERTY()
	UPrimitiveComponent* CurrentLadder = nullptr;
};
