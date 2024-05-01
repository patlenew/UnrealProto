// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attacks/BaseAttack.h"
#include "PlayerTestAttack.generated.h"

UCLASS()
class VAMPIRESURVIVORRPG_API APlayerTestAttack : public ABaseAttack
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APlayerTestAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
