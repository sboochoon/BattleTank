// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"

/* ATank Constructor
Sets default values
*/
ATank::ATank()
{
 	// We don't need the Tank to tick every frame
	PrimaryActorTick.bCanEverTick = false;
}

/* BeginPlay
Called when the game starts or when spawned
*/
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

/* SetupPlayerInputComponent
Called to bind functionality to input
*/
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

/* AimAt
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair
*/
void ATank::AimAt(FVector AimLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(AimLocation, LaunchSpeed);
}

/* Fire
Tells the tank to fire a projectile if allowed based on reload time
*/
void ATank::Fire()
{
	//True if ReloadTimeInSeconds has elapsed since LastFireTime, False if not
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	//Tank can fire
	if (Barrel && isReloaded)
	{
		//Spawn <AProjectile> at "LaunchPoint" with socket's location and rotation
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("LaunchPoint")), Barrel->GetSocketRotation(FName("LaunchPoint")));

		//Launch the spawned projectile
		Projectile->LaunchProjectile(LaunchSpeed);

		//Update LastFireTime to current because we've just fired
		LastFireTime = FPlatformTime::Seconds();
	}
}