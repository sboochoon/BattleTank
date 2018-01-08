// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = ("Collision") )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float DegreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 20.0f; //Sensible default
	
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevation = 30.0f; //Sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevation = 0.0f; //Sensible default


};
