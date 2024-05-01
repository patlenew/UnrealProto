// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureCharacter.h"

#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "PlayerCharacter.h"
#include "Data/CharacterDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VampireSurvivorRPG/Components/HealthComponent.h"

// Sets default values
ACreatureCharacter::ACreatureCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	m_HealthBarBackground = CreateSpriteComponent(TEXT("Health Bar Background"));
	m_HealthBarBackground->SetupAttachment(RootComponent);
	m_HealthBarBackground->SetSpriteColor(FColor::Black);

	m_HealthBarFill = CreateSpriteComponent(TEXT("Health Bar Fill"));
	m_HealthBarFill->SetupAttachment(m_HealthBarBackground);
	m_HealthBarBackground->SetSpriteColor(FColor::Green);

	const float half = m_HealthBarBackground->GetSprite()->GetSourceSize().X * 0.5f;
	
	// Should move the filler also
	m_HealthBarBackground->SetRelativeLocation(FVector(-half, 0.0f, 120.0f));
	m_HealthBarFill->SetRelativeLocation(FVector(0.0f, 0.01f, 0.0f));
}

void ACreatureCharacter::Internal_Setup()
{
	Super::Internal_Setup();

	GetHealthComponent()->Init(GetData()->CharacterSheet.BaseHealth, m_HealthBarFill);
}

UPaperSpriteComponent* ACreatureCharacter::CreateSpriteComponent(FName Name)
{
	UPaperSpriteComponent* spriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(Name);
	UPaperSprite* sprite = LoadObject<UPaperSprite>(nullptr, TEXT("WhiteSprite'/Game/Art/Sprites/WhiteSprite.WhiteSprite'"));

	if(sprite == nullptr)
	{
		DEBUG_LOG("null sprite");
		return nullptr;
	}

	DEBUG_LOG("Sprite loaded!");

	spriteComponent->SetSprite(sprite);
	
	return spriteComponent;
}

// Called when the game starts or when spawned
void ACreatureCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ACreatureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateMovement(DeltaTime);
}

void ACreatureCharacter::OnTakeDamage(float Damage)
{
	Super::OnTakeDamage(Damage);

	m_burstingAway = true;
	m_currentBurstTime = 0.0f;
	m_burstingStartPos = GetActorLocation();
	
	m_burstingDirection = GetActorLocation() - m_PlayerCharacter->GetActorLocation(); // Away from the player
	m_burstingDirection.Z = 0.0;
	
	m_burstingDirection.Normalize();
	m_verticalSpeed = m_burstHeight * FMath::Sin(FMath::DegreesToRadians(45.0f));
	
	const float gravity = -9.8f;
	m_totalAirDuration = 2 * m_verticalSpeed / FMath::Abs(gravity);
	
	DEBUG_LOG(FString::Printf( TEXT("Time until land: %f"), m_totalAirDuration ));
}

void ACreatureCharacter::UpdateMovement(float DeltaTime)
{
	if (m_burstingAway)
	{
		m_currentBurstTime += DeltaTime * 10.0f;
		
		const float gravity = -9.8f;
		const float halfGravity = gravity * 0.5f;
		
		float zPosition = m_burstingStartPos.Z + (m_verticalSpeed * m_currentBurstTime) + (halfGravity * m_currentBurstTime * m_currentBurstTime);

		float tPos = m_currentBurstTime / m_totalAirDuration;
		FVector newPos = m_burstingStartPos + (m_burstingDirection * m_burstDistance * tPos);
		newPos.Z = zPosition;
		
		SetActorLocation(newPos);
		
		if (m_totalAirDuration <= m_currentBurstTime)
		{
			m_burstingAway = false;
		}
	}
	else
	{
		FVector toPlayer = m_PlayerCharacter->GetActorLocation() - GetActorLocation();
		toPlayer.Normalize();
		
		SetActorLocation(GetActorLocation() + toPlayer * 100.0f * GetWorld()->GetDeltaSeconds());

		const FRotator toPlayerRot = toPlayer.Rotation();
		SetActorRotation( toPlayerRot );
	}
}

// Called to bind functionality to input
void ACreatureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

