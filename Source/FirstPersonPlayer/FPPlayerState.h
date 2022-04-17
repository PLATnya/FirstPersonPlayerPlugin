// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Actor.h"
#include "FPPlayerState.generated.h"

struct FGameplayTag;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFPOnOwnedTagsChangedDelegate, FGameplayTag, Tag);

UCLASS()
class FIRSTPERSONPLAYER_API AFPPlayerState : public AActor, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:

	FFPOnOwnedTagsChangedDelegate OnOwnedTagAdd;
	FFPOnOwnedTagsChangedDelegate OnOwnedTagRemove;


	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
	
	void AddOwnedTag(const FGameplayTag& _Tag);
	void AddOwnedTags(const FGameplayTagContainer& _Tags);
	
	void RemoveOwnedTag(const FGameplayTag& _Tag);
	void RemoveOwnedTags(const FGameplayTagContainer& _Tags);
private:
	
	FGameplayTagContainer OwnedTags;
	
};
