// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BaseAttackData.h"
#include "GameFramework/Actor.h"
#include "BaseAttack.generated.h"

struct FAttackData;

UCLASS()
class VAMPIRESURVIVORRPG_API ABaseAttack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Effects
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AHitEffect> HitEffect;

	// TODO: Feed elsewhere?
	// Data

	void SetupForPlayer();
	void SetupForEnemy();
	
	void Trigger();

private:
	UPROPERTY(EditAnywhere)
	UBaseAttackData* m_AttackDataAsset;

	FAttackData m_AttackData;
	
	bool m_InCooldown;
	float m_CooldownTime;

	void SetInCooldown();
	void UpdateCooldown(float DeltaTime);
};
