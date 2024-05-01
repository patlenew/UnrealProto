// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "HealthComponent.generated.h"

class UPaperSpriteComponent;


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRESURVIVORRPG_API UHealthComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void OnRegister() override;
	virtual void OnComponentCreated() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Rounded to the nearest whole number
	int GetCurrentHealth() const;
	int GetMaxHealth() const;

	bool IsDead() const { return m_CurrentHealth <= 0; }

	// TODO: Add Data Asset
	void Init(float MaxHealth);
	void Init(float MaxHealth, UPaperSpriteComponent* healthBar);
	void SetCurrentHealth(float NewHealth);
	void SetMaxHealth(float NewMaxHealth);
	void LoseHealth(float Damage);
	
private:

	float m_CurrentHealth;
	float m_MaxHealth;
	UPaperSpriteComponent* m_healthBar;
};
