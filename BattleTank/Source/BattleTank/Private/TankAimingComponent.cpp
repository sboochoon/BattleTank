// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/GameplayStaticsTypes.h"

/* UTankAimingComponent Constructor
Sets default values for this component's properties
*/
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

/* AimAt
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt
Get the AimLocation and LaunchSpeed from Tank.cpp
Calculate if we can fire at our crosshair worldspace location based on SuggestProjectileVelocity:
If we can then send a unit direction vector based on our AimLocation to our MoveBarrelTowards function
If we can not fire based on SuggestProjectileVelocity then it means that it is impossible for our projectile to reach the crosshair worldspace coords
*/
void UTankAimingComponent::AimAt(FVector AimLocation, float LaunchSpeed)
{
	if (!Barrel || !Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

/* MoveBarrelTowards
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt/TankAimingComponent/AimAt ONLY if we have a valid aiming solution
Send the appropriate rotation values to the Turret and Barrel
*/
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!Barrel || !Turret) { return; }

	//Find difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto RotationAmount = AimRotator - BarrelRotator;

	//Tell the Barrel to Elevate by the specified Pitch
	Barrel->Elevate(RotationAmount.Pitch);

	//Tell the Turret to Rotate by the specified Yaw
	Turret->Rotate(RotationAmount.Yaw);
}