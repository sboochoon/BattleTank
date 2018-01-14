// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"
#include "BattleTank.h"
#include "Engine/World.h"

#define OUT //written in the place where the variable is updated

/* BeginPlay
Called when the game starts or when spawned
*/
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Get the tank that has been spawned into the world for us (at the PlayerStart location)
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank ID: %s"), *ControlledTank->GetName());
	}
	
}

/* Tick
Called every frame
*/
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Every tick we call AimAt and send it the worldspace coords of where we are aiming ONLY if we have a valid aiming location
	AimTowardsCrosshair();
}

/* GetControlledTank
Returns the <ATank>GetPawn() of PlayerController
*/
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

/* AimTowardsCrosshair
TICK: Called every tick via TankPlayerController/Tick
Start moving the barrel toward the crosshair UI in the world
*/
void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; //Out parameter to store our worldspace coords of where we're aiming at

	// Set OutHitLocation only if we're aiming in a valid location
	if (GetSightRayHitLocation(OUT OutHitLocation))
	{
		//Tell our tank to move the turret and barrel to OutHitLocation
		GetControlledTank()->AimAt(OutHitLocation);
	}
}

/* GetSightRayHitLocation
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair
Uses GetLookDirection and GetLookVectorHitLocation and feeds them the crosshair location
*/
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position based on our screen size
	int32 OutViewportSizeX, OutViewportSizeY;
	GetViewportSize(OUT OutViewportSizeX, OUT OutViewportSizeY);
	auto ScreenLocation = FVector2D(OutViewportSizeX*CrossHairXLocation, OutViewportSizeY*CrossHairYLocation);

	FVector OutLookDirection; //Out parameter to store the worldspace coords of our UI crosshair

	//Get worldspace coords of UI crosshair...
	if (GetLookDirection(ScreenLocation, OUT OutLookDirection))
	{
		//...Use those crosshair coords to do a raycast and update OutHitLocation if we hit a valid location, or not
		GetLookVectorHitLocation(OUT OutHitLocation, OutLookDirection);
	}
	return true;
}

/* GetLookDirection
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/GetSightRayHitLocation
Sets the value of OutLookDirection, which is an OUT variable to the worldspace coordinates of the UI crosshair
*/
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
	FVector WorldLocation; //To be discarded since we don't need this info

	//"De-project" the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, OUT WorldLocation, OUT OutLookDirection);
}

/* GetLookVectorHitLocation
TICK: Called every tick via TankPlayerController/Tick/AimTowardsCrosshair/GetSightRayHitLocation
Sets the value of OutHitLocation, which is an OUT variable to the location in the world where the crosshair UI is pointing at
*/
bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector OutLookDirection) const
{
	FHitResult OutLineHit; //Interim variable to hold our raycast info
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); //Start location for the raycast
	auto EndLocation = StartLocation + (OutLookDirection * LineTraceRange); //End location for the raycast

	// Raycast out from StartLocation to EndLocation and if we hit a valid location based on ECC_Visibility (What we can see in the world, not the sky), then add hit info to OutLineHit
	if (GetWorld()->LineTraceSingleByChannel(OUT OutLineHit, StartLocation, EndLocation, ECC_Visibility))
	{
		OutHitLocation = OutLineHit.Location;
		return true;
	}
	// We're aiming at a non-valid location, so return a zero vector (this will cause our turret and barrel to return to the initial positions)
	else
	{
		OutHitLocation = FVector(0);
		return false;
	}
}