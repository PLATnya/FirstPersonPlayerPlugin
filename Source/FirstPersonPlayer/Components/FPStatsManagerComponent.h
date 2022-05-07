

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FPStatsManagerComponent.generated.h"

struct FGameplayTag;


DECLARE_DELEGATE_RetVal(float, FGetStatValue);
DECLARE_DELEGATE_RetVal(float&, FGetStatValueRef);


UCLASS()
class UFPStat : public UObject 
{
	GENERATED_BODY()

public:
	//calls every frame
//	FGetStatValueOnChange OnTickGetValueDelegate;

	//calls only ones on max value reaching
//	FGetStatValueOnChange OnFullGetValueDelegate;
	//calls only ones on min value reaching
//	FGetStatValueOnChange OnEmptyGetValueDelegate;


	FGetStatValueRef GetValueRefDelegate;

	FGetStatValue GetMinValueDelegate;
	FGetStatValue GetMaxValueDelegate;

	void Update();

private:

	bool bShouldTryTickOnFull = false;
	bool bShouldTryTickOnEmpty = false;

	bool IsEmptyReached = true;
	bool IsFullReached = false;
private:

};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONPLAYER_API UFPStatsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPStatsManagerComponent();

	void AddStat(FGameplayTag _StatTag, TSubclassOf<UFPStat> StatClass);
	UFPStat* GetStat(FGameplayTag _StatTag) const { return *StatInfosInstances.Find(_StatTag); }


private:
	void UpdateStats();
	
	TMap<FGameplayTag, UFPStat*> StatInfosInstances;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, TSubclassOf<UFPStat>> StatInfos;
};
