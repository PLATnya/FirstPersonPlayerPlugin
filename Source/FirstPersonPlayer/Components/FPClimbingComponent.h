//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPClimbingComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONPLAYER_API UFPClimbingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFPClimbingComponent();

	UPrimitiveComponent* GetGrabbedPrimitiveComp() const { return pPrimitiveGrabbedObstacle; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UPrimitiveComponent* pPrimitiveGrabbedObstacle = nullptr;
};