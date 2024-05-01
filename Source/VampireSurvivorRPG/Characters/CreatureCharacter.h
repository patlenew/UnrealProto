// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "CreatureCharacter.generated.h"

class APlayerCharacter;
class UPaperSpriteComponent;
class UHealthComponent;

UCLASS()
class VAMPIRESURVIVORRPG_API ACreatureCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACreatureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnTakeDamage(float Damage) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	UPaperSpriteComponent* m_HealthBarBackground;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	UPaperSpriteComponent* m_HealthBarFill;

protected:
	virtual void Internal_Setup() override;

private:
	// Bursting away from the player like a ballistic trajectory
	bool m_burstingAway;
	FVector3d m_burstingDirection;
	FVector3d m_burstingStartPos;
	float m_verticalSpeed;
	float m_currentBurstTime;
	float m_totalAirDuration;	// Time until the creature lands on the ground
	
	APlayerCharacter* m_PlayerCharacter;

	// Editables
	UPROPERTY(EditAnywhere, Category="Movement")
	float m_burstDistance = 500.0f;

	UPROPERTY(EditAnywhere, Category="Movement")
	float m_burstHeight = 75.0f;
	
	UPaperSpriteComponent* CreateSpriteComponent(FName Name);

	void UpdateMovement(float DeltaTime);
};
