// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "Data/CharacterDataAsset.h"
#include "VampireSurvivorRPG/Components/HealthComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter(): m_Data(nullptr)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_HealthComponent = FindComponentByClass<UHealthComponent>();
}

void ABaseCharacter::Move()
{
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::Setup(UCharacterDataAsset* DataAsset)
{
	m_Data = DataAsset;
	
	Internal_Setup();
}

void ABaseCharacter::Internal_Setup()
{
	m_HealthComponent->Init(m_Data->CharacterSheet.BaseHealth);
}

void ABaseCharacter::Die()
{
	Destroy();
}

void ABaseCharacter::OnTakeDamage(float Damage)
{
	if(m_HealthComponent == nullptr)
	{
		DEBUG_LOG("Health component is null");
		return;
	}
	
	m_HealthComponent->LoseHealth(Damage);

	if(m_HealthComponent->IsDead())
	{
		Die();
	}
}
