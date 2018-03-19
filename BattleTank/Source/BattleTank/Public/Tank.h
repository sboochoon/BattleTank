// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

///Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

/**
*
*/

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
///Functions
/*Constructor*/
	// Sets default values for this pawn's properties
	ATank();

/*Actions*/
	// Fire function
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();										

///TICK Functions
	//TICK: TankPlayerController/Tick/AimTowardsCrosshair
	// Aim at a FVector world location
	virtual void AimAt(FVector AimLocation);

///Variables

protected:
///Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

///Variables
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:	
///Functions
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

///Variables
	//Speed of the projectile being fired, can only be edited in main BP class, not an instance of it (EditDefaultsOnly)
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0f; // 40 m/s

	// Property to determine fire rate, can only be edited in main BP class, not an instance of it (EditDefaultsOnly)
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	// Allows user to add an AProjectile actor in BP, can only be edited in main BP class, not an instance of it (EditDefaultsOnly)
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; // TSubclassOf<Class> is an alternative to UClass*, however it limits what can be added to only the <Class> specified
	
	// Var to store local reference of Barrel
	UTankBarrel* Barrel = nullptr; // Needed for getting the socket location and rotation for launching projectile

	// Var to hold time since last fired (used to calculate reloading)
	double LastFireTime = 0; // *double* because we're using FPlatformTime::Seconds()					
};