//


#include "FPClimbingComponent.h"

#include "Components/CapsuleComponent.h"
#include "FirstPersonPlayer/FPCharacter.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UFPClimbingComponent::UFPClimbingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


bool UFPClimbingComponent::TryClimb(UPrimitiveComponent* ClimbingComponent)
{
	if (!IsClimbable(ClimbingComponent))
	{
		return false;
	}
	
	AFPCharacter* OwnerCharacter = GetOwnedCharacter();
	if(!ensure(IsValid(OwnerCharacter))){ return false; }

	const FVector CurrentCharacterLocation = OwnerCharacter->GetActorLocation();
	FVector GrabPointWithOffset = GetClimbingPoint(ClimbingComponent, CurrentCharacterLocation, (CurrentCharacterLocation - ClimbingComponent->GetComponentLocation()).GetSafeNormal());
	const UCapsuleComponent* OwnerCharacterCapsule = OwnerCharacter->GetCapsuleComponent();

	auto StartClimbing = [this, OwnerCharacter, GrabPointWithOffset, ClimbingComponent]()
	{
		LastClimbComponent = ClimbingComponent;
		ClimbingPoint = GrabPointWithOffset;
		OwnerCharacter->bSimGravityDisabled = true;
		bIsClimbing = true;
		GetOwnedCharacter()->GetCharacterMovement()->SetMovementMode(MOVE_None);
		GetOwnedCharacter()->SetActorEnableCollision(false);
		GetOwnedCharacter()->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	};
	
	TArray<FHitResult> OutHits;
	if (!UKismetSystemLibrary::CapsuleTraceMulti(OwnerCharacter, CurrentCharacterLocation, GrabPointWithOffset,
		OwnerCharacterCapsule->GetScaledCapsuleRadius(), OwnerCharacterCapsule->GetScaledCapsuleHalfHeight(),
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic),
		false, {}, EDrawDebugTrace::None, OutHits, true))
	{
		StartClimbing();
		return true;	
	}
	
	if (OutHits.Num() == 0)
	{
		StartClimbing();
		return true;
	}

	return false;
}

bool UFPClimbingComponent::IsClimbable_Implementation(UPrimitiveComponent* ClimbingComponent) const
{
	return true;
}

void UFPClimbingComponent::ClimbHorizontal(float AxisFactor)
{
	if (!bIsClimbing  || AxisFactor == 0)
	{
		return;
	}

	const FVector PlayerForwardVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation().Vector();
	ClimbInDirection(PlayerForwardVector *  AxisFactor);
}

void UFPClimbingComponent::ClimbVertical(float AxisFactor)
{
	if (!bIsClimbing || AxisFactor == 0)
	{
		return;
	}
	
	const FVector PlayerForwardVector = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation().Vector();
	ClimbInDirection(PlayerForwardVector *  AxisFactor);
}

// Called when the game starts
void UFPClimbingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFPClimbingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsClimbing)
	{
		const FVector MoveDirection = (ClimbingPoint - GetOwnedCharacter()->GetActorLocation()).GetSafeNormal();
		GetOwnedCharacter()->GetCharacterMovement()->MoveSmooth(MoveDirection * 200.0f, DeltaTime);
		//GetOwnedCharacter()->AddActorWorldOffset(MoveDirection * 5.0f);
		if (IsValid(LastClimbComponent))
		UE_LOG(LogTemp, Warning, TEXT("Climbing: %s"), *GetNameSafe(LastClimbComponent->GetAttachmentRootActor()));
	}
}

void UFPClimbingComponent::ClimbInDirection(FVector Direction)
{
	AFPCharacter* OwnerCharacter = GetOwnedCharacter();
	if(!ensure(IsValid(OwnerCharacter))){ return; }

	const UCapsuleComponent* OwnerCharacterCapsule = OwnerCharacter->GetCapsuleComponent();

	
	const FVector ClimbingDirectionStart = OwnerCharacter->GetActorLocation();
	const FVector ClimbingDirectionEnd = OwnerCharacter->GetActorLocation() + Direction.GetSafeNormal() * 100;
	const float CharacterCapsuleRadius = OwnerCharacterCapsule->GetScaledCapsuleRadius();
	const float CharacterCapsuleHalfHeight = OwnerCharacterCapsule->GetScaledCapsuleHalfHeight();

	float TraceCapsuleHeight = CharacterCapsuleHalfHeight / 2;
	//DrawDebugCapsule(GetWorld(),  ClimbingDirectionEnd, TraceCapsuleHeight, CharacterCapsuleRadius,
	//	FQuat::Identity,FColor::Blue, true);
	TArray<FHitResult> OutHits;
	if (!UKismetSystemLibrary::CapsuleTraceMulti(OwnerCharacter, ClimbingDirectionStart, ClimbingDirectionEnd,
		CharacterCapsuleRadius, TraceCapsuleHeight,
		UEngineTypes::ConvertToTraceType(ECC_WorldStatic), false, {},
		EDrawDebugTrace::None, OutHits, true))
	{
		return;
	}

	if (OutHits.Num() == 0)
	{
		return;
	}

	bool bIsSameClimbHit = false;
	bool bIsAnotherClimbHit = false;

	FHitResult SameHit;
	TArray<UPrimitiveComponent*> ClimbableComponents;
	for (auto& Hit: OutHits)
	{
		if (Hit.Component == LastClimbComponent)
		{
			SameHit = Hit;
			bIsSameClimbHit = true;
		}
		else
		{
			UPrimitiveComponent* ClimbCandidateComponent = Hit.GetComponent();
			//if (IsClimbable(ClimbCandidateComponent))
			if (IsClimbable(ClimbCandidateComponent))
			{
				ClimbableComponents.Add(ClimbCandidateComponent);
				bIsAnotherClimbHit = true;
			}
		}
	}

	if (!bIsSameClimbHit && bIsAnotherClimbHit)
	{
		for(UPrimitiveComponent* Component: ClimbableComponents)
		{
			if (TryClimb(Component))
			{
				return;
			}
		}
	}
	else if (bIsSameClimbHit && !bIsAnotherClimbHit)
	{
		ClimbingPoint = GetClimbingPoint(LastClimbComponent, SameHit.Location, SameHit.Normal);
	}
}

FVector UFPClimbingComponent::GetClimbingPoint(UPrimitiveComponent* ClimbingOnComponent, const FVector& Location, const FVector& LocationNormal) const 
{
	AFPCharacter* OwnerCharacter = GetOwnedCharacter();
	if(!ensure(IsValid(OwnerCharacter))){ return FVector::ZeroVector; }

	FVector GrabPoint = GetPointOnEdge(ClimbingOnComponent, Location);
	
	//DrawDebugBox(GetWorld(), GrabPoint, FVector(20.0f), FColor::Red, true);
	
	const FVector GrabPointCharacterOffset = LocationNormal * 100.0f;
	FVector GrabPointWithOffset = GrabPoint + FVector(GrabPointCharacterOffset.X, GrabPointCharacterOffset.Y, 0.0f);
	//DrawDebugBox(GetWorld(), GrabPointWithOffset, FVector(20.0f), FColor::Green, true);
	return GrabPointWithOffset;
}

FVector UFPClimbingComponent::GetPointOnEdge(UPrimitiveComponent* ClimbingOnComponent, const FVector Location) const
{
	const FVector LocalSpaceClosestPoint = ClimbingOnComponent->GetComponentTransform().InverseTransformPosition(Location);
	const FVector BoxSize = ClimbingOnComponent->Bounds.BoxExtent;
	FVector GrabPoint = FVector(LocalSpaceClosestPoint.X, LocalSpaceClosestPoint.Y, 50.0f);


	if (GrabPoint.X <= 50 && GrabPoint.X >= -50 && GrabPoint.Y <= 50 && GrabPoint.Y >= -50)
	{
		if (FMath::Abs(BoxSize.X - FMath::Abs(GrabPoint.X / 50) * BoxSize.X) < FMath::Abs(BoxSize.Y - FMath::Abs(GrabPoint.Y) / 50 * BoxSize.Y))
		{
			GrabPoint.X = GrabPoint.X > 0 ? 50 : -50;
		}
		else
		{
			GrabPoint.Y = GrabPoint.Y > 0 ? 50 : -50;
		}
	}
	else
	{
		auto TransformAxisValue = [](float Value)
		{
			if (Value > 50) return 50.0f;
			if (Value < -50) return -50.0f;
			return Value;
		};
		GrabPoint = FVector(TransformAxisValue(GrabPoint.X), TransformAxisValue(GrabPoint.Y), 50);
	}
	

	return ClimbingOnComponent->GetComponentTransform().TransformPosition( GrabPoint);
}

AFPCharacter* UFPClimbingComponent::GetOwnedCharacter() const
{
	auto* pCharacter = Cast<AFPCharacter>(GetOwner());
	if(!ensure(pCharacter)){ return nullptr; }

	return pCharacter;
}
