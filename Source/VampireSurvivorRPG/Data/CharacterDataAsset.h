// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterDataAsset.generated.h"


class ABaseAttack;

USTRUCT()
struct FCharacterSheet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString Name;

	UPROPERTY(EditAnywhere)
	float BaseHealth;
	
	UPROPERTY(EditAnywhere)
	TArray<TSoftClassPtr<ABaseAttack>> Attacks;
};

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORRPG_API UCharacterDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FCharacterSheet CharacterSheet;
};
