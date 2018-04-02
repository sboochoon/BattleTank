// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
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

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	if (AmmoCount <= 0)
	{
		FiringState = EFiringStatus::OutOfAmmo;
	}
	//True if ReloadTimeInSeconds has elapsed since LastFireTime, False if not
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringStatus::Aiming;
	}
	else
	{
		FiringState = EFiringStatus::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelForward = Barrel->GetForwardVector();

	return !BarrelForward.Equals(AimDirection, 0.01);
}

/* AimAt
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt
Get the AimLocation and LaunchSpeed from Tank.cpp
Calculate if we can fire at our crosshair worldspace location based on SuggestProjectileVelocity:
If we can then send a unit direction vector based on our AimLocation to our MoveBarrelTowards function
If we can not fire based on SuggestProjectileVelocity then it means that it is impossible for our projectile to reach the crosshair worldspace coords
*/
void UTankAimingComponent::AimAt(FVector AimLocation)
{
	//AimDirection = AimLocation;

	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("LaunchPoint"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OUT OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

/* MoveBarrelTowards
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt/TankAimingComponent/AimAt ONLY if we have a valid aiming solution
Send the appropriate rotation values to the Turret and Barrel
*/
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel)) { return; }

	//Find difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto RotationAmount = AimRotator - BarrelRotator;

	//Tell the Barrel to Elevate by the specified Pitch
	Barrel->Elevate(RotationAmount.Pitch);

	//Tell the Turret to Rotate by the specified Yaw
	if (FMath::Abs(RotationAmount.Yaw) < 180)
	{
		Turret->Rotate(RotationAmount.Yaw);
	}
	
	else
	{
		Turret->Rotate(-RotationAmount.Yaw);
	}
}

/* Fire
Tells the tank to fire a projectile if allowed based on reload time
*/
void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringStatus::Reloading && FiringState != EFiringStatus::OutOfAmmo)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }
		//Spawn <AProjectile> at "LaunchPoint" with socket's location and rotation
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("LaunchPoint")), Barrel->GetSocketRotation(FName("LaunchPoint")));

		//Launch the spawned projectile
		Projectile->LaunchProjectile(LaunchSpeed);

		//Update LastFireTime to current because we've just fired
		LastFireTime = FPlatformTime::Seconds();

		//Reduce Ammo
		AmmoCount--;
	}
}

int UTankAimingComponent::GetAmmo() const
{
	return AmmoCount;
}

void UTankAimingComponent::SetAmmo(int amount)
{
	AmmoCount = amount;
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
