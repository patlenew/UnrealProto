// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackTargetType.h"
#include "Engine/DataAsset.h"
#include "BaseAttackData.generated.h"

/**
 * 
 */


USTRUCT()
struct FAttackData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float Range;

	UPROPERTY(EditAnywhere)
	float Cooldown;

	UPROPERTY(EditAnywhere)
	float Duration;

	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	float AreaOfEffect;

	// Unshown
	AttackTargetType TargetType;
};

UCLASS()
class VAMPIRESURVIVORRPG_API UBaseAttackData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FAttackData AttackData;
};
