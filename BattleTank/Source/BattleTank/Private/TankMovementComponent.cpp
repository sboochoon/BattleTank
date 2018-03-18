// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"



void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveFoward(float Throw) 
{
	if (!LeftTrack || !RightTrack) { return; }

	//Move the tank tracks based on how fast we want to go (-1 to +1)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Turn)
{
	if (!LeftTrack || !RightTrack) { return; }

	//Turn the tank tracks based on how fast we want to go (-1 to +1)
	LeftTrack->SetThrottle(Turn);
	RightTrack->SetThrottle(-Turn);
}


