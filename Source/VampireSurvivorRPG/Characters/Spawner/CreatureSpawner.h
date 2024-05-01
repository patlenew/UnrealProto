// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CreatureSpawner.generated.h"

class ACreatureCharacter;

UCLASS()
class VAMPIRESURVIVORRPG_API ACreatureSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACreatureSpawner();

	void Setup(const TArray<ACreatureCharacter*>& creatures);
	void SetData(float timeBetweenSpawns, uint16 maxCreatureCount, ACreatureCharacter* creatureTemplate);
	
	void InitCreatures(class UCharacterDataAsset* DataAsset);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateSpawning();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	TArray<ACreatureCharacter*> m_Creatures;
	ACreatureCharacter* m_CreatureTemplate;
	UCharacterDataAsset* m_CreatureDataAsset;

	float m_TimeBetweenSpawns;
	float m_TimeSinceLastSpawn;
	uint16 m_MaxCreatureCount;

	FVector GetSpawnPos() const;
};
