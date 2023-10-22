


#include "FPLadderMovementComponent.h"

#include "Components/CapsuleComponent.h"
#include "FirstPersonPlayer/FPCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UFPLadderMovementComponent::UFPLadderMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UFPLadderMovementComponent::JumpFromClimb()
{
	if (!bOnLadder )
	{
		return;
	}
	bOnLadder = false;
	GetOwnedCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	GetOwnedCharacter()->SetActorEnableCollision(true);
	GetOwnedCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetOwnedCharacter()->Jump();

	const FVector PlayerForwardVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation().Vector();
	GetOwnedCharacter()->GetCharacterMovement()->AddImpulse(PlayerForwardVector * LadderOffJumpForce);

}

bool UFPLadderMovementComponent::TryClimb(UPrimitiveComponent* LadderComponent)
{
	FVector CharacterLocalOnLadder = LadderComponent->GetComponentTransform().InverseTransformPosition(GetOwnedCharacter()->GetActorLocation());

	FVector CharacterTargetLocalOnLadder = CharacterLocalOnLadder;
	if (CharacterTargetLocalOnLadder.Y > 50 ) 
	{
		CharacterTargetLocalOnLadder.Y = 50;
	}
	else if (CharacterTargetLocalOnLadder.Y < -50)
	{
		CharacterTargetLocalOnLadder.Y = -50;
	}

	FVector LadderNormal = LadderComponent->GetForwardVector();
	if (CharacterTargetLocalOnLadder.X >= 0)
	{
		CharacterTargetLocalOnLadder.X = 50;
	}
	else
	{
		LadderNormal = -LadderNormal;
		CharacterTargetLocalOnLadder.X = -50;
	}

	
	FVector CharacterOnLadderTarget = LadderComponent->GetComponentTransform().TransformPosition(CharacterTargetLocalOnLadder);
	CharacterOnLadderTarget += LadderNormal * 100;

	UCapsuleComponent* CharacterCapsule = GetOwnedCharacter()->GetCapsuleComponent();
	
	TArray<FHitResult> OutHits;
	if (UKismetSystemLibrary::CapsuleTraceMulti(GetOwnedCharacter(), GetOwnedCharacter()->GetActorLocation(), CharacterOnLadderTarget,
		CharacterCapsule->GetScaledCapsuleRadius(), CharacterCapsule->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, {},
		EDrawDebugTrace::None, OutHits, true))
	{
		return false;
	}

	if (OutHits.Num() != 0)
	{
		return false;
	}
	
	LadderOnLocation = CharacterOnLadderTarget;
	bOnLadder = true;
	CurrentLadder = LadderComponent;

	GetOwnedCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_None);
	GetOwnedCharacter()->SetActorEnableCollision(false);
	GetOwnedCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	return true;
}

void UFPLadderMovementComponent::ClimbVertical(float AxisFactor)
{
	if (!bOnLadder )
	{
		return;
	}
	if (FMath::IsNearlyZero(AxisFactor))
	{
		return;
	}

	LadderOnLocation = GetOwnedCharacter()->GetActorLocation() + AxisFactor * CurrentLadder->GetUpVector()*50;
	FVector Local = CurrentLadder->GetComponentTransform().InverseTransformPosition(LadderOnLocation);
	if (Local.Z > 50)
	{
		LadderOnLocation = CurrentLadder->GetComponentTransform().TransformPosition(FVector(0, 0, 65));
		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			bOnLadder = false;
			GetOwnedCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			GetOwnedCharacter()->SetActorEnableCollision(true);
			GetOwnedCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}, 1.5f, false);
	}
}

AFPCharacter* UFPLadderMovementComponent::GetOwnedCharacter() const
{
	auto* pCharacter = Cast<AFPCharacter>(GetOwner());
	if(!ensure(pCharacter)){ return nullptr; }

	return pCharacter;
}

void UFPLadderMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bOnLadder)
	{
		const FVector MoveDirection = (LadderOnLocation - GetOwnedCharacter()->GetActorLocation()).GetSafeNormal();
		GetOwnedCharacter()->GetCharacterMovement()->MoveSmooth(MoveDirection * 200.0f, DeltaTime);
	}
}


