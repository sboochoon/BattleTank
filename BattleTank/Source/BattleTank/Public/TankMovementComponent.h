// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
 //BlueprintSpawnableComponent so we can add it as a component to our actor in BP
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

///Functions
public:
	//Setup the tracks
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet);

	//Forward/backward movement
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveFoward(float Throw);

	//Right/left turning
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Turn);

	//Used for AI to navigate the navmesh
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

///Variables
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
