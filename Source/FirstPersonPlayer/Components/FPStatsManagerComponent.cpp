


#include "FPStatsManagerComponent.h"


// Sets default values for this component's properties
UFPStatsManagerComponent::UFPStatsManagerComponent()
{

	
	//PrimaryComponentTick.bCanEverTick = false;



}


void UFPStatsManagerComponent::AddStat(FGameplayTag _StatTag, TSubclassOf<UFPStat> StatClass)
{
	StatInfosInstances.Add(_StatTag, NewObject<UFPStat>(this, StatClass));
}

void UFPStatsManagerComponent::UpdateStats()
{
	for (auto& StatInfo : StatInfosInstances) {
		StatInfo.Value->Update();
	}
}

void UFPStat::Update()
{
	//CurrentValue = OnTickGetValueDelegate.Broadcast(CurrentValue);


}
