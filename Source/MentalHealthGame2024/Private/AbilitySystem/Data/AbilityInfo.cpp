// Copyright Team SortaSoda MHGJ 2024


#include "AbilitySystem/Data/AbilityInfo.h"

#include "MentalHealthGame2024/MentalHealthGame2024LogChannels.h"

FAlmaAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
	for (const FAlmaAbilityInfo& Info : AbilityInformation)
	{
		if (Info.AbilityTag == AbilityTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogMentalHealthGame2024, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAlmaAbilityInfo();
}