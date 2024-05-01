// Fill out your copyright notice in the Description page of Project Settings.


#include "Attacks/BaseAttack.h"

#include "HitEffect.h"
#include "Data/BaseAttackData.h"

// Sets default values
ABaseAttack::ABaseAttack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseAttack::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCooldown(GetWorld()->DeltaTimeSeconds);
}

void ABaseAttack::SetupForPlayer()
{
	m_AttackData = m_AttackDataAsset->AttackData;
	m_AttackData.TargetType = AttackTargetType::ATT_Enemy;
}

void ABaseAttack::SetupForEnemy()
{
	m_AttackData = m_AttackDataAsset->AttackData;
	m_AttackData.TargetType = AttackTargetType::ATT_Player;
}

void ABaseAttack::Trigger()
{
	if (m_InCooldown) return;
	
	AHitEffect* hitEffect = GetWorld()->SpawnActor<AHitEffect>(HitEffect, GetActorLocation(), GetActorRotation());
	hitEffect->Setup(m_AttackData, GetActorLocation());
	
	SetInCooldown();
}

void ABaseAttack::SetInCooldown()
{
	m_InCooldown = true;
	m_CooldownTime = m_AttackDataAsset->AttackData.Cooldown;
}

void ABaseAttack::UpdateCooldown(float DeltaTime)
{
	if (!m_InCooldown) return;

	m_CooldownTime -= DeltaTime;

	//DEBUG_LOG("Cooldown: " + FString::SanitizeFloat(m_CooldownTime));
	
	if (m_CooldownTime <= 0.0f)
	{
		//DEBUG_LOG("nO MORE COOLDOWN!");
		
		m_InCooldown = false;
	}
}

