// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


/* Initialize
Sets tank tracks, for use in BP
*/
void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

/* IntendMoveFoward
Forward/backward movement
*/
void UTankMovementComponent::IntendMoveFoward(float Throw) 
{
	if (!LeftTrack || !RightTrack) { return; }

	//Move the tank tracks based on how fast we want to go (-1 to +1)
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

/* IntendTurnRight
Right/left turning
*/
void UTankMovementComponent::IntendTurnRight(float Turn)
{
	if (!LeftTrack || !RightTrack) { return; }

	//Turn the tank tracks based on how fast we want to go (-1 to +1)
	LeftTrack->SetThrottle(Turn);
	RightTrack->SetThrottle(-Turn);
}

/* RequestDirectMove
Used for AI to navigate the navmesh
*/
void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	//Make variables for forward vector and vector for where tank wants to go
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	//Move forward
	IntendMoveFoward(FVector::DotProduct(AIForwardIntention, TankForward));

	//Turn
	auto TurnAmount = FVector::CrossProduct(AIForwardIntention, TankForward);
	IntendTurnRight(TurnAmount.Z);
}


