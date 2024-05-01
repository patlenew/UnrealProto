// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerTestAttack.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(m_mappingContext, 0);
		}
	}

	m_camera = GetComponentByClass<UCameraComponent>();
	m_springArm = GetComponentByClass<USpringArmComponent>();

	ABaseAttack* testAttack = GetWorld()->SpawnActor<ABaseAttack>(m_testAttack.Get(), GetActorLocation(), GetActorRotation());
	testAttack->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
	EquipAttack(testAttack);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(m_JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(m_MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(m_LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

		// Attacking
		EnhancedInputComponent->BindAction(m_BaseAttackAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Attack);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D movementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement
		AddMovementInput(GetActorForwardVector(), movementVector.Y);
		AddMovementInput(GetActorRightVector(), movementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D lookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(-lookAxisVector.X);

		FRotator rotator = m_springArm->GetRelativeRotation().Add(-lookAxisVector.Y, 0.0f, 0.0f);
		double pitch = rotator.Pitch;
		pitch = FMath::Clamp(pitch, m_lookPitchMinMax.min, m_lookPitchMinMax.max);

		rotator.Pitch = pitch;
		
		m_springArm->SetRelativeRotation(rotator);
	}
}

void APlayerCharacter::EquipAttack(ABaseAttack* Attack)
{
	m_equippedAttack = Attack;
	m_equippedAttack->SetupForPlayer();
}

void APlayerCharacter::Attack()
{
	m_equippedAttack->Trigger();
}

