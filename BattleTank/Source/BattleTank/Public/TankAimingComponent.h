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
	Locked,
	OutOfAmmo
};

///Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

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

	// Fire function
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	// Get Ammo
	UFUNCTION(BlueprintCallable, Category = "Setup")
	int GetAmmo() const;

	// Set Ammo
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetAmmo(int amount);

	EFiringStatus GetFiringState() const;
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
<<<<<<< HEAD

	//Ammo for tank
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 15;
=======
>>>>>>> a19e2e319599715a579b2e8d96a3b5b4494620d4

///TICK Functions
	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt
	//Get the AimLocation and LaunchSpeed from Tank.cpp, 
	//Calculate if we can fire at our crosshair worldspace location based on SuggestProjectileVelocity,
	//If we can then send a unit direction vector based on our AimLocation to our MoveBarrelTowards function.
	//If we can not fire based on SuggestProjectileVelocity then it means that it is impossible for our projectile to reach the crosshair worldspace coords
	void AimAt(FVector AimLocation);

	//Enum for firing states
	UPROPERTY(BlueprintReadOnly , Category = "Firing")
	EFiringStatus FiringState = EFiringStatus::Reloading;


private:
///TICK Functions
	//TICK: TankPlayerController/Tick/AimTowardsCrosshair/Tank/AimAt/TankAimingComponent/AimAt ONLY if we have a valid aiming solution
	//Send the appropriate rotation values to the Turret and Barrel
	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	//BeginPlay of UActorComponent
	virtual void BeginPlay() override;

	//TickComponent of UActorComponent
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

///Variables
	// Barrel for this tank that the aiming component is attached to
	UTankBarrel* Barrel = nullptr;

	// Turret for this tank that the aiming component is attached to
	UTankTurret* Turret = nullptr;

	// Var to hold time since last fired (used to calculate reloading)
	double LastFireTime = 0; // *double* because we're using FPlatformTime::Seconds()	

	FVector AimDirection;

<<<<<<< HEAD

=======
	//Ammo for tank
	int AmmoCount = 15;
>>>>>>> a19e2e319599715a579b2e8d96a3b5b4494620d4
};