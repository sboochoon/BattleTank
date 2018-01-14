// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

//BlueprintSpawnableComponent so we can add it as a static mesh component to our actor in BP, hide the Collision category in the Details panel
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
///Functions
	// Raise or lower the barrel by the RelativeSpeed up to MaxElevation or down to MinElevation
	// -1 is max downward speed, +1 is max upward speed
	void Elevate(float RelativeSpeed);
	
private:
///Variables
	// Movement in degrees that the barrel can raise or lower per second
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 10.0f;
	
	// Maximum elevation that the barrel can raise to
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 40.0f;

	// Minimum elevation that the barrel can lower to
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.0f;
};