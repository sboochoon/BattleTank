// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

///ENUMS
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked
};

///Forward Declarations
class UTankBarrel;
class UTankTurret;

/**
*
*/

//BlueprintSpawnableComponent so we can add it as a component to our actor in BP
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
///Functions

	//Setup the aiming component
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

/*Constructor*/
	// Sets default values for this component's properties
	UTankAimingComponent();

///TICK Functions
	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt
	//Get the AimLocation and LaunchSpeed from Tank.cpp, 
	//Calculate if we can fire at our crosshair worldspace location based on SuggestProjectileVelocity,
	//If we can then send a unit direction vector based on our AimLocation to our MoveBarrelTowards function.
	//If we can not fire based on SuggestProjectileVelocity then it means that it is impossible for our projectile to reach the crosshair worldspace coords
	void AimAt(FVector AimLocation, float LaunchSpeed);

	//Enum for firing states
	UPROPERTY(BlueprintReadOnly , Category = "Firing")
	EFiringStatus FiringState = EFiringStatus::Reloading;


private:
///TICK Functions
	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt/TankAimingComponent/AimAt ONLY if we have a valid aiming solution
	//Send the appropriate rotation values to the Turret and Barrel
	void MoveBarrelTowards(FVector AimDirection);

///Variables
	// Barrel for this tank that the aiming component is attached to
	UTankBarrel* Barrel = nullptr;

	// Turret for this tank that the aiming component is attached to
	UTankTurret* Turret = nullptr;
};