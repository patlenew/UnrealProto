// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivorGameMode.h"
#include "Characters/Spawner/CreatureSpawner.h"
#include "PlayerCharacter.h"
#include "Characters/CreatureCharacter.h"
#include "Kismet/GameplayStatics.h"

void ASurvivorGameMode::StartPlay()
{
	Super::StartPlay();

	Setup();
}

void ASurvivorGameMode::Setup()
{
	TArray<AActor*> creatures;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACreatureCharacter::StaticClass(), creatures);

	for (AActor* actor : creatures)
	{
		if (ACreatureCharacter* creature = Cast<ACreatureCharacter>(actor))
		{
			m_LevelCreatures.Add(creature);
		}
	}
	
	m_CreatureSpawner = GetWorld()->SpawnActor<ACreatureSpawner>();
	m_CreatureSpawner->Setup(m_LevelCreatures);
	m_CreatureSpawner->InitCreatures(m_TestCreatureData);
	m_CreatureSpawner->SetData(5.0f, 10, m_CreatureClass.GetDefaultObject());
	
	TArray<AActor*> player;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerCharacter::StaticClass(), player);
	
	m_PlayerCharacter = Cast<APlayerCharacter>(player[0]); // Should be only one
	m_PlayerCharacter->Setup(m_PlayerData);
}
