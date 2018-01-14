// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

/* Rotate
Rotate the turret clockwise or anticlockwise by RelativeSpeed
-1 is max anticlockwise speed, +1 is max clockwise speed
*/
void UTankTurret::Rotate(float RelativeSpeed)
{
	//Clamp to -1 and +1
	auto ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.f);

	//Move turret the right amount this frame, given max rotation speed and frame time
	auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	//UE4 SetRelativeRotation function with FRotator(Pitch, Yaw, Roll)
	SetRelativeRotation(FRotator(0.f, RawNewRotation, 0.f));
}