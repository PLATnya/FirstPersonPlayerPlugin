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

void AFPPlayerState::AddOwnedTags(const FGameplayTagContainer& _Tags)
{
	OwnedTags.AppendTags(_Tags);

	TArray<FGameplayTag> TagsArray;
	_Tags.GetGameplayTagArray(TagsArray);
	
	for(auto Tag: TagsArray)
	{
		OnOwnedTagAdd.Broadcast(Tag);
	}
}

void AFPPlayerState::RemoveOwnedTag(const FGameplayTag& _Tag)
{
	OwnedTags.RemoveTag(_Tag);
	OnOwnedTagRemove.Broadcast(_Tag);
}

void AFPPlayerState::RemoveOwnedTags(const FGameplayTagContainer& _Tags)
{
	OwnedTags.RemoveTags(_Tags);

	TArray<FGameplayTag> TagsArray;
	_Tags.GetGameplayTagArray(TagsArray);
	
	for(auto Tag: TagsArray)
	{
		OnOwnedTagRemove.Broadcast(Tag);
	}
}
