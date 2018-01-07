// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Setter method for Barrel
	void SetBarrelReference(UStaticMeshComponent* BarrelToSet);

	//Output log
	void OutputLog(FString TankName, FVector Location);

	//Aiming function
	void AimAt(FVector AimLocation, float LaunchSpeed);

private:
	UStaticMeshComponent* Barrel = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	
};
