// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "Utils/MinMax.h"
#include "PlayerCharacter.generated.h"

using namespace UP;

class UInputAction;
class UInputMappingContext;
class ABaseAttack;

/**
 * 
 */
UCLASS()
class VAMPIRESURVIVORRPG_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	
private:
	class UCameraComponent* m_camera;
	class USpringArmComponent* m_springArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Test, meta=(AllowPrivateAccess="true"))
	TSubclassOf<ABaseAttack> m_testAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess="true"))
	UInputMappingContext* m_mappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_BaseAttackAction;

// Rotation Settings
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FMinMax m_lookPitchMinMax;

// Equipped Attack
private:
	ABaseAttack* m_equippedAttack;
	TArray<ABaseAttack*> m_attacks;

	void EquipAttack(ABaseAttack* Attack);
	void Attack();
};
