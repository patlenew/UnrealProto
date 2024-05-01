// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BaseAttackData.h"
#include "GameFramework/Actor.h"
#include "HitEffect.generated.h"

class USphereComponent;
using namespace UP;

class UAttackComponent;

UCLASS()
class VAMPIRESURVIVORRPG_API AHitEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitEffect();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Setup(FAttackData attackData, const FVector& location);
	
private:

	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* m_ParticleSystem;

	UPROPERTY(EditAnywhere)
	float m_TimeBeforeRemoved = 5.0f;

	FTimerHandle m_DestroyTimerHandle;
	UAttackComponent* m_AttackComponent;

	FAttackData m_AttackData;
	
	// Temp
	UPROPERTY(EditAnywhere)
	USphereComponent* m_SphereComponent;
	
	// Methods
	void OnTimerUpdate();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit );
};
