// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacks/BaseAttack.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UCharacterDataAsset;
class UHealthComponent;

UCLASS()
class VAMPIRESURVIVORRPG_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Move();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Setup(UCharacterDataAsset* DataAsset);

	UCharacterDataAsset* GetData() const { return m_Data; }

	virtual void OnTakeDamage(float Damage);

protected:
	virtual void Internal_Setup();
	virtual void Die();
	
	UHealthComponent* GetHealthComponent() const { return m_HealthComponent; }
	UCharacterDataAsset* GetDataAsset() const { return m_Data; }
	
private:
	UCharacterDataAsset* m_Data;

	UPROPERTY(EditAnywhere, Category="Health")
	UHealthComponent* m_HealthComponent;
};
