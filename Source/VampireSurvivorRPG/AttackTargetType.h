// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class AttackTargetType : uint8
{
  		ATT_Player		UMETA(DisplayName = "Player"),
	    ATT_Enemy		UMETA(DisplayName = "Enemy"),
};
