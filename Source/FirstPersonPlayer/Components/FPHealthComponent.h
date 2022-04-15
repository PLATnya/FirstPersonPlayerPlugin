// 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMOnHealthChanging, float, OldHealth, float, NewHealth);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONPLAYER_API UFPHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	FMOnDeath OnDeath;
	FMOnHealthChanging OnHealthChanging;
	
	UFPHealthComponent();
	UFUNCTION(BlueprintCallable)
	void AddHealthPoints(float _HealthPoints);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	float HealthPoints = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxHealthPoints = 100.0f;
private:

	bool bIsAlive = true;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
};
