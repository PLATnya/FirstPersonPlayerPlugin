// 

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagAssetInterface.h"
#include "GameFramework/Character.h"
#include "FPCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFPOnOwnedTagsChangedDelegate, FGameplayTag, Tag);

UCLASS()
class FIRSTPERSONPLAYER_API AFPCharacter : public ACharacter, public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	FFPOnOwnedTagsChangedDelegate OnOwnedTagAdd;
	FFPOnOwnedTagsChangedDelegate OnOwnedTagRemove;

	
	// Sets default values for this character's properties
	AFPCharacter();

	//tag asset interface
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void AddOwnedTag(const FGameplayTag& _Tag);
	void RemoveOwnedTag(const FGameplayTag& _Tag);
private:
	virtual void OnForwardMove(float _AxisValue);
	virtual void OnRightMove(float _AxisValue);

	FGameplayTagContainer OwnedTags;
};
