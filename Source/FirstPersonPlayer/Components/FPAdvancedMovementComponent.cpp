//


#include "FPAdvancedMovementComponent.h"

#include "FirstPersonPlayer/FPCharacter.h"

UFPAdvancedMovementComponent::UFPAdvancedMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//PimaryComponentTick.TickGroup = TG_PrePhysics;
	//PrimaryComponentTick.bCanEverTick = true;
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

AFPCharacter* UFPAdvancedMovementComponent::GetCharacterOwner() const
{
	return Cast<AFPCharacter>(GetOwner());
}

UCharacterMovementComponent* UFPAdvancedMovementComponent::GetCharacterMovement() const
{
	AFPCharacter* OwnerCharacter = GetCharacterOwner();
	if(!IsValid(OwnerCharacter))
	{
		return nullptr;
	}

	return OwnerCharacter->GetCharacterMovement();
}