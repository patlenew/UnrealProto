// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::OnRegister()
{
	Super::OnRegister();
}

void UHealthComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UHealthComponent::GetCurrentHealth() const 
{
	return static_cast<int>(m_CurrentHealth);
}

int UHealthComponent::GetMaxHealth() const 
{
	return static_cast<int>(m_MaxHealth);
}

void UHealthComponent::Init(float MaxHealth)
{
	SetMaxHealth(MaxHealth);
	SetCurrentHealth(MaxHealth);
}

void UHealthComponent::Init(float MaxHealth, UPaperSpriteComponent* healthBar)
{
	m_healthBar = healthBar;
	
	SetMaxHealth(MaxHealth);
	SetCurrentHealth(MaxHealth);
}

void UHealthComponent::SetCurrentHealth(float NewHealth)
{
	m_CurrentHealth = NewHealth;

	if(m_healthBar != nullptr)
	{
		const float healthPercentage = m_CurrentHealth / m_MaxHealth;

		DEBUG_LOG(FString::Printf(TEXT("%f"), healthPercentage));
		
		m_healthBar->SetRelativeScale3D(FVector(healthPercentage, 1.0f, 1.0f));
	}
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	m_MaxHealth = NewMaxHealth;
}

void UHealthComponent::LoseHealth(float Damage)
{
	SetCurrentHealth(m_CurrentHealth - Damage);
}

