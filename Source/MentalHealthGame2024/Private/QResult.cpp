#include "QResult.h"

// Default constructor
UQResult::UQResult()
{
	Name = TEXT("");
	Score = 0.0f;
	Time = 0.0f;
}

// Parameterized constructor
void UQResult::Initialize(const FString& InName, float InScore, float InTime)
{
	Name = InName;
	Score = InScore;
	Time = InTime;
}
