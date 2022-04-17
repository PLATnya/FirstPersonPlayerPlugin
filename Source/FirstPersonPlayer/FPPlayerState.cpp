// 


#include "FPPlayerState.h"


//
void AFPPlayerState::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	TagContainer.AppendTags(OwnedTags);
}


void AFPPlayerState::AddOwnedTag(const FGameplayTag& _Tag)
{
	OwnedTags.AddTag(_Tag);
	OnOwnedTagAdd.Broadcast(_Tag);
}

void AFPPlayerState::RemoveOwnedTag(const FGameplayTag& _Tag)
{
	OwnedTags.RemoveTag(_Tag);
	OnOwnedTagRemove.Broadcast(_Tag);
}