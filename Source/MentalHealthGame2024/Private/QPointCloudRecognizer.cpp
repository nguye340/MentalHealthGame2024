// Fill out your copyright notice in the Description page of Project Settings.
#include "QPointCloudRecognizer.h"
#include "QGeometry.h"
#include "QGesture.h"
#include "Math/UnrealMathUtility.h"

bool UQPointCloudRecognizer::bUseEarlyAbandoning = true;
bool UQPointCloudRecognizer::bUseLowerBounding = true;

FString UQPointCloudRecognizer::Classify(const UQGesture* Candidate, const TArray<UQGesture*>& TemplateSet)
{
    float MinDistance = TNumericLimits<float>::Max();
    FString GestureClass = "";

    for (const UQGesture* Template : TemplateSet)
    {
        float Distance = GreedyCloudMatch(Candidate, Template, MinDistance);
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            GestureClass = Template->Name;
        }
    }
    return GestureClass;
}

float UQPointCloudRecognizer::GreedyCloudMatch(const UQGesture* Gesture1, const UQGesture* Gesture2, float MinSoFar)
{
    int32 NumPoints = Gesture1->Points.Num();
    float Eps = 0.5f;
    int32 Step = FMath::FloorToInt(FMath::Pow(NumPoints, 1.0f - Eps));

    if (bUseLowerBounding)
    {
        TArray<float> LB1 = ComputeLowerBound(Gesture1->Points, Gesture2->Points, Gesture2->LUT, Step);
        TArray<float> LB2 = ComputeLowerBound(Gesture2->Points, Gesture1->Points, Gesture1->LUT, Step);

        for (int32 i = 0, IndexLB = 0; i < NumPoints; i += Step, IndexLB++)
        {
            if (LB1[IndexLB] < MinSoFar)
                MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));

            if (LB2[IndexLB] < MinSoFar)
                MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    }
    else
    {
        for (int32 i = 0; i < NumPoints; i += Step)
        {
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture1->Points, Gesture2->Points, i, MinSoFar));
            MinSoFar = FMath::Min(MinSoFar, CloudDistance(Gesture2->Points, Gesture1->Points, i, MinSoFar));
        }
    }
    return MinSoFar;
}

TArray<float> UQPointCloudRecognizer::ComputeLowerBound(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, const TArray<FNestedArray>& LUT, int32 Step)
{
    int32 NumPoints = Points1.Num();
    TArray<float> LB;
    LB.SetNum(NumPoints / Step + 1);
    TArray<float> SAT;
    SAT.SetNum(NumPoints);

    LB[0] = 0;
    int32 LUTScaleFactor = UQGesture::GetLUTScaleFactor();
    for (int32 i = 0; i < NumPoints; i++)
    {
        int32 Index = LUT[Points1[i].intY / LUTScaleFactor].InnerArray[Points1[i].intX / LUTScaleFactor];
        float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[Index]);
        SAT[i] = (i == 0) ? Distance : SAT[i - 1] + Distance;
        LB[0] += (NumPoints - i) * Distance;
    }

    for (int32 i = Step, IndexLB = 1; i < NumPoints; i += Step, IndexLB++)
    {
        LB[IndexLB] = LB[0] + i * SAT[NumPoints - 1] - NumPoints * SAT[i - 1];
    }
    return LB;
}

float UQPointCloudRecognizer::CloudDistance(const TArray<FQPoint>& Points1, const TArray<FQPoint>& Points2, int32 StartIndex, float MinSoFar)
{
    int32 NumPoints = Points1.Num();
    TArray<int32> IndexesNotMatched;
    IndexesNotMatched.SetNum(NumPoints);

    for (int32 j = 0; j < NumPoints; j++)
    {
        IndexesNotMatched[j] = j;
    }

    float Sum = 0;
    int32 i = StartIndex;
    int32 Weight = NumPoints;
    int32 IndexNotMatched = 0;

    do
    {
        int32 Index = -1;
        float MinDistance = TNumericLimits<float>::Max();
        for (int32 j = IndexNotMatched; j < NumPoints; j++)
        {
            float Distance = UQGeometry::SqrEuclideanDistance(Points1[i], Points2[IndexesNotMatched[j]]);
            if (Distance < MinDistance)
            {
                MinDistance = Distance;
                Index = j;
            }
        }
        IndexesNotMatched[Index] = IndexesNotMatched[IndexNotMatched];
        Sum += (Weight--) * MinDistance;

        if (bUseEarlyAbandoning && Sum >= MinSoFar)
        {
            return Sum;
        }

        i = (i + 1) % NumPoints;
        IndexNotMatched++;
    } while (i != StartIndex);

    return Sum;
}
