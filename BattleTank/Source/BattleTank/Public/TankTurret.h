// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */

 //BlueprintSpawnableComponent so we can add it as a static mesh component to our actor in BP, hide the Collision category in the Details panel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision"))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
///Functions
	// Rotate the turret clockwise or anticlockwise by RelativeSpeed
	// -1 is max anticlockwise speed, +1 is max clockwise speed
	void Rotate(float RelativeSpeed);

private:
///Variables
	// Movement in degrees that the turret can rotate per second
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 25.0f;
};