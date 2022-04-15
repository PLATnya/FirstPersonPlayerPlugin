// 


#include "FPPlayerState.h"


// Sets default values
AFPPlayerState::AFPPlayerState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFPPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

