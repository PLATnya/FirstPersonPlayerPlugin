// 


#include "FPHealthComponent.h"
#include "GameFramework/Character.h"


UFPHealthComponent::UFPHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFPHealthComponent::AddHealthPoints(float _HealthPoints)
{
	const float OldHealth = HealthPoints;
	HealthPoints += _HealthPoints;
	
	OnHealthChanging.Broadcast(OldHealth, HealthPoints);
}

void UFPHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	auto* pCharacter = Cast<ACharacter>(GetOwner());
	if (IsValid(pCharacter))
	{
		if (!pCharacter->OnTakeAnyDamage.IsAlreadyBound(this, &UFPHealthComponent::OnTakeAnyDamage))
		{
			pCharacter->OnTakeAnyDamage.AddDynamic(this, &UFPHealthComponent::OnTakeAnyDamage);
		}
	}
}


void UFPHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage,
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (!bIsAlive)
	{
		return;
	}

	const float OldHealth = HealthPoints;
	HealthPoints = FMath::Clamp(HealthPoints - Damage, 0.0f, MaxHealthPoints);

	OnHealthChanging.Broadcast(OldHealth, HealthPoints);
	if (HealthPoints <= KINDA_SMALL_NUMBER)
	{
		bIsAlive = false;
		OnDeath.Broadcast();
	}	
}
