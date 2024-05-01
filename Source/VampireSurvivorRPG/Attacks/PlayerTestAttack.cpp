// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTestAttack.h"


// Sets default values
APlayerTestAttack::APlayerTestAttack()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerTestAttack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerTestAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

