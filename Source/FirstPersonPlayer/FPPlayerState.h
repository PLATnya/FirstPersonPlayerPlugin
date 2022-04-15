// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPPlayerState.generated.h"

UCLASS()
class FIRSTPERSONPLAYER_API AFPPlayerState : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFPPlayerState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
