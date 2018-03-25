// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"


UTankTrack::UTankTrack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

//While the track is on the ground
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//Movement
	DriveTrack();

	//Remove sideways sliding
	ApplySidewaysForce();

	//Reset Throttle
	CurrentThrottle = 0.f;
}

void UTankTrack::ApplySidewaysForce()
{
	auto DeltaTime = GetWorld()->GetDeltaSeconds();

	//Calculate SlippageSpeed
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	//Acceleration = Speed / Time. We want the opposite acceleration, ie not in the right vector we are currently slipping in

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	//Apply a sideways force (F = ma)
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Divide by 2 because we have 2 tracks
	TankRoot->AddForce(CorrectionForce);
}

/* SetThrottle
Sets a throttle between -1 and +1 and AddForceAtLocation to move the tank
*/
void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//Calculate force to apply based on Throttle and the TrackMaxDrivingForce
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;

	//Component location of the track at (0,0,0)
	auto ForceLocation = GetComponentLocation();

	//Get the root of the tank, cast it to a UPrimitiveComponent so we can apply force to it
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


