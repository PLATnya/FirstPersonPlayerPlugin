//


#include "FPClimbingComponent.h"

#include "Components/CapsuleComponent.h"
#include "FirstPersonPlayer/FPCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFPClimbingComponent::UFPClimbingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UFPClimbingComponent::TryGrab()
{
	const UWorld* pWorld = GetWorld();
	if(!ensure(IsValid(pWorld))){ return false; }

	AFPCharacter* pOwnerCharacter = GetOwnedCharacter();
	if(!ensure(IsValid(pOwnerCharacter))){ return false; }

	const UCapsuleComponent* pCharacterCapsuleComp = pOwnerCharacter->GetCapsuleComponent();
	if(!ensure(IsValid(pCharacterCapsuleComp))){ return false; }

	const float CapsuleRadius = pCharacterCapsuleComp->GetScaledCapsuleRadius();
	const float HalfCapsuleHeight = pCharacterCapsuleComp->GetScaledCapsuleHalfHeight();


	const FVector TraceDirection = pOwnerCharacter->GetActorForwardVector();
	const FVector CharacterLocation = pOwnerCharacter->GetActorLocation();

	const FVector TraceStart = FVector::ZeroVector;
	const FVector TraceEnd = FVector::ZeroVector;


	FHitResult OutLedgeHit;

	const bool bHitLedge = UKismetSystemLibrary::CapsuleTraceSingleByProfile(this, TraceStart, TraceEnd, CapsuleRadius, HalfCapsuleHeight,TEXT("IgnoreOnlyPawn"), false, {pOwnerCharacter},EDrawDebugTrace::ForOneFrame,
		OutLedgeHit, true);
}

// Called when the game starts
void UFPClimbingComponent::BeginPlay()
{
	Super::BeginPlay();
}

AFPCharacter* UFPClimbingComponent::GetOwnedCharacter() const
{
	auto* pCharacter = Cast<AFPCharacter>(GetOwner());
	if(!ensure(pCharacter)){ return nullptr; }

	return pCharacter;
}