// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

/* ATank Constructor
Sets default values
*/
ATank::ATank()
{
 	// We don't need the Tank to tick every frame
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers as added at construction
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")); //CreateDefaultSubobject<Class>(FName("NAME")) adds a component of <Class> with NAME by default to the actor
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

/* SetBarrelReference
Function that will be setup in BP so that TankAimingComponent knows what mesh the Barrel is
*/
void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet; //Local reference to be used in Fire()
}

/* SetTurretReference 
Function that will be setup in BP so that TankAimingComponent knows what mesh the Turret is
*/
void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

/* AimAt
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair
*/
void ATank::AimAt(FVector AimLocation)
{
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