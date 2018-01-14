// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

/* SetThrottle
Sets a throttle between -1 and +1 and AddForceAtLocation to move the tank
*/
void UTankTrack::SetThrottle(float Throttle)
{
	//TODO Clamp Throttle value to -1 and 1 so player cannot override the tank speed

	//Calculate force to apply based on Throttle and the TrackMaxDrivingForce
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

	//Component location of the track at (0,0,0)
	auto ForceLocation = GetComponentLocation();

	//Get the root of the tank, cast it to a UPrimitiveComponent so we can apply force to it
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


