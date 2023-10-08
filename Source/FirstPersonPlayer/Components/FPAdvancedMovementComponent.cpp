//


#include "FPAdvancedMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "FirstPersonPlayer/FPCharacter.h"
#include "Tasks/Task.h"

UFPAdvancedMovementComponent::UFPAdvancedMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PrimaryComponentTick.TickGroup = TG_PrePhysics;
	PrimaryComponentTick.bCanEverTick = true;
}


void UFPAdvancedMovementComponent::StartSprinting()
{
	if(bIsSprinting)
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if(!ensureMsgf(IsValid(CharacterMovement), TEXT("Character Movement component is missing to start sprinting")))
	{
		return;
	}

	BuffMaxWalkSpeed = CharacterMovement->MaxWalkSpeed;
	CharacterMovement->MaxWalkSpeed = RunSpeed;

	bIsSprinting = true;
}

void UFPAdvancedMovementComponent::StopSprinting()
{
	if(!bIsSprinting)
	{
		return;
	}

	UCharacterMovementComponent* CharacterMovement = GetCharacterMovement();
	if(!ensureMsgf(IsValid(CharacterMovement), TEXT("Character Movement component is missing to stop sprinting")))
	{
		return;
	}

	CharacterMovement->MaxWalkSpeed = BuffMaxWalkSpeed;

	bIsSprinting = false;
}

void UFPAdvancedMovementComponent::StartCrouch()
{
	bIsCrouching = true;
}

void UFPAdvancedMovementComponent::UpdateCrouching(float DeltaTime)
{
	float CapsuleHalfHeight = BuffHalfHeight - (BuffHalfHeight / 2) * (CrouchSmoothTime / CrouchSmoothMaxTime);
	if (CapsuleHalfHeight != 0.0f)
	{
		
		GetCharacterCapsule()->SetCapsuleHalfHeight(CapsuleHalfHeight);
	}

	CrouchSmoothTime = FMath::Clamp(CrouchSmoothTime + (bIsCrouching ? DeltaTime : -DeltaTime), 0, CrouchSmoothMaxTime);
}

void UFPAdvancedMovementComponent::StopCrouch()
{
	bIsCrouching = false; 
}

void UFPAdvancedMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateCrouching(DeltaTime);
}

void UFPAdvancedMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	BuffHalfHeight = GetCharacterCapsule()->GetScaledCapsuleHalfHeight();
}

AFPCharacter* UFPAdvancedMovementComponent::GetCharacterOwner() const
{
	return Cast<AFPCharacter>(GetOwner());
}

UCharacterMovementComponent* UFPAdvancedMovementComponent::GetCharacterMovement() const
{
	const AFPCharacter* OwnerCharacter = GetCharacterOwner();
	if(!IsValid(OwnerCharacter))
	{
		return nullptr;
	}

	return OwnerCharacter->GetCharacterMovement();
}

UCapsuleComponent* UFPAdvancedMovementComponent::GetCharacterCapsule() const
{
	const AFPCharacter* OwnerCharacter = GetCharacterOwner();
	if(!IsValid(OwnerCharacter))
	{
		return nullptr;
	}

	return OwnerCharacter->GetCapsuleComponent();
}
