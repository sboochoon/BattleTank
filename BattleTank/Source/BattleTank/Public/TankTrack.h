// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and to apply forces to the tank.
 */
 //BlueprintSpawnableComponent so we can add it as a static mesh component to our actor in BP, hide the Collision category in the Details panel
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
///Functions
	// Sets a throttle between -1 and +1 and AddForceAtLocation to move the tank
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);
	
///Variables
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float TrackMaxDrivingForce = 40000000.f; // Force = mass x acc: 40000 tons x 1000 cm/s^2
};
