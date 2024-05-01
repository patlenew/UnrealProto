// Fill out your copyright notice in the Description page of Project Settings.


#include "HitEffect.h"

#include "AttackComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Components/SphereComponent.h"
#include "Data/BaseAttackData.h"

// Sets default values
AHitEffect::AHitEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHitEffect::BeginPlay()
{
	Super::BeginPlay();

	m_SphereComponent = FindComponentByClass<USphereComponent>();
	m_SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AHitEffect::OnHit);
	
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_ParticleSystem, GetActorLocation(), GetActorRotation());

	GetWorld()->GetTimerManager().SetTimer(m_DestroyTimerHandle, this, &AHitEffect::OnTimerUpdate, 0.1f, true);
}

void AHitEffect::EndPlay(const EEndPlayReason::Type endPlayReason)
{
	Super::EndPlay(endPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(m_DestroyTimerHandle);
}

// Called every frame
void AHitEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitEffect::Setup(FAttackData attackData, const FVector& location)
{
	m_AttackData = attackData;
	
	SetActorLocation(location);
	
	// Root component
	UAttackComponent* attackComponent = Cast<UAttackComponent>(AddComponentByClass(UAttackComponent::StaticClass(), true, GetActorTransform(), false));
	AddInstanceComponent(attackComponent);

	attackComponent->SetData(attackData);
	
	m_AttackComponent = attackComponent;

	if(m_AttackComponent == nullptr)
	{
		DEBUG_LOG("AttackComponent is null");
	}

	m_SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AHitEffect::OnTimerUpdate()
{
	m_TimeBeforeRemoved -= 1.0f;

	if (m_TimeBeforeRemoved <= 0.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(m_DestroyTimerHandle);
		Destroy();
	}
}

void AHitEffect::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit )
{
	bool hasHit = false;
	
	if (m_AttackData.TargetType == AttackTargetType::ATT_Enemy)
	{
		if (OtherActor->ActorHasTag(FName("Enemy")))
		{
			DEBUG_LOG("HIT ENEMY");
			hasHit = true;
		}
	}
	else if (m_AttackData.TargetType == AttackTargetType::ATT_Player)
	{
		if (OtherActor->ActorHasTag(FName("Player")))
		{
			DEBUG_LOG("HIT PLAYER");
			hasHit = true;
		}
	}

	if(hasHit)
	{
		ABaseCharacter* character = Cast<ABaseCharacter>(OtherActor);

		if (character != nullptr)
		{
			character->OnTakeDamage(m_AttackComponent->GetDamage());
		}
		else
		{
			FString text = OtherActor->GetName();
			FString message = FString::Printf(TEXT("Character is null %s"),  *text);
			
			DEBUG_LOG(message);
		}

	}
}

