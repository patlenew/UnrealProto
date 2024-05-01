// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SurvivorGameMode.generated.h"

class UCharacterDataAsset;
class ACreatureSpawner;
class ACreatureCharacter;
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORRPG_API ASurvivorGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	void Setup();

	ACreatureSpawner* GetCreatureSpawner() const { return m_CreatureSpawner; }
	
private:
	UPROPERTY(EditAnywhere)
	APlayerCharacter* m_PlayerCharacter;

	UPROPERTY(EditAnywhere)
	TArray<ACreatureCharacter*> m_LevelCreatures;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ACreatureCharacter> m_CreatureClass;

	UPROPERTY(EditAnywhere)
	USceneComponent* m_PlayerStart;

	UPROPERTY(EditAnywhere)
	UCharacterDataAsset* m_PlayerData;

	UPROPERTY(EditAnywhere)
	UCharacterDataAsset* m_TestCreatureData;
	
	ACreatureSpawner* m_CreatureSpawner;
};
