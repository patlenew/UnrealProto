#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"
#include "MinMax.generated.h"

USTRUCT(BlueprintType)
struct  VAMPIRESURVIVORRPG_API FMinMax
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinMax")
	float min;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MinMax")
	float max;

	float GetRandomValue() const;
};
