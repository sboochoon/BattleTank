// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

/* Elevate
Raise or lower the barrel by the RelativeSpeed up to MaxElevation or down to MinElevation
-1 is max downward speed, +1 is max upward speed
*/
void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Clamp to -1 and +1
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	//Move barrel the right amount this frame, given max elevation speed and frame time
	auto ElevationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	//UE4 SetRelativeRotation function with FRotator(Pitch, Yaw, Roll)
	SetRelativeRotation(FRotator(FMath::Clamp<float>(RawNewElevation, MinElevation, MaxElevation), 0.f, 0.f));
}