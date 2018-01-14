// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

///Forward Declarations
class ATank;

/**
*
*/

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
///TICK Functions
	//TICK: TankPlayerController
	// Called every frame
	virtual void Tick(float DeltaTime) override;

///Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns the <ATank>GetPawn() of PlayerController
	ATank* GetControlledTank() const;

///Variables
	// X Location of the crosshair UI on the screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrossHairXLocation = 0.5f;

	// Y Location of the crosshair UI on the screen
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CrossHairYLocation = 0.33333f;

	// Distance of the raycast for determining if we hit anything
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LineTraceRange = 100000.0f;

private:
///TICK Functions
	//TICK: TankPlayerController/Tick
	// Start moving the barrel toward the crosshair UI in the world
	void AimTowardsCrosshair();

	//TICK: TankPlayerController/Tick/AimTowardsCrosshair
	// Uses GetLookDirection and GetLookVectorHitLocation and feeds them the crosshair location
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/GetSightRayHitLocation
	// Sets the value of OutLookDirection, which is an OUT variable to the worldspace coordinates of the UI crosshair
	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/GetSightRayHitLocation
	// Sets the value of OutHitLocation, which is an OUT variable to the location in the world where the crosshair UI is pointing at
	bool GetLookVectorHitLocation(FVector& OutHit, FVector OutLookDirection) const;
};