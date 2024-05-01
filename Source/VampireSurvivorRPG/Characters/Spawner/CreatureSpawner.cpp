// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureSpawner.h"

#include "PlayerCharacter.h"
#include "Characters/CreatureCharacter.h"
#include "Data/CharacterDataAsset.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ACreatureSpawner::ACreatureSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACreatureSpawner::Setup(const TArray<ACreatureCharacter*>& creatures)
{
	for (ACreatureCharacter* creature : creatures)
	{
		m_Creatures.Add(creature);
	}
}

void ACreatureSpawner::SetData(float timeBetweenSpawns, uint16 maxCreatureCount, ACreatureCharacter* creatureTemplate)
{
	m_MaxCreatureCount = maxCreatureCount;
	m_TimeBetweenSpawns = timeBetweenSpawns;
	m_CreatureTemplate = creatureTemplate;
}

// Called when the game starts or when spawned
void ACreatureSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreatureSpawner::InitCreatures(UCharacterDataAsset* DataAsset)
{
	for (ACreatureCharacter* creature : m_Creatures)
	{
		creature->Setup(DataAsset);
	}

	m_CreatureDataAsset = DataAsset;
}

void ACreatureSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSpawning();
}

void ACreatureSpawner::UpdateSpawning()
{
	if (m_Creatures.Num() < m_MaxCreatureCount)
	{
		m_TimeSinceLastSpawn += GetWorld()->GetDeltaSeconds();
		if (m_TimeSinceLastSpawn >= m_TimeBetweenSpawns)
		{
			m_TimeSinceLastSpawn = 0.0f;
			
			// Spawn a creature
			ACreatureCharacter* creature = GetWorld()->SpawnActor<ACreatureCharacter>(m_CreatureTemplate->GetClass());
			creature->SetActorLocation(GetSpawnPos());
			creature->Setup(m_CreatureDataAsset);

			m_Creatures.Add(creature);
		}
	}

	// Cleanup
	for (int i = m_Creatures.Num() - 1; i >= 0; --i)
	{
		if (!IsValid(m_Creatures[i]) || m_Creatures[i]->IsActorBeingDestroyed()) 
		{
			m_Creatures.RemoveAt(i);
		}
	}
}

FVector ACreatureSpawner::GetSpawnPos() const
{
	const APlayerCharacter* player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	const FVector playerPos = player->GetActorLocation();

	const float randomX = FMath::RandRange(0.2f, 1.0f);
	const float randomY = FMath::RandRange(0.2f, 1.0f);
	
	const FVector randomAroundPlayer = FVector(playerPos.X + FMath::Cos(randomX) * 1000.f, playerPos.Y + FMath::Sin(randomY) * 1000.f, playerPos.Z);

	return randomAroundPlayer;
}

