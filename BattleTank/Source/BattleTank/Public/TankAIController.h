// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

///Forward Declarations

/**
*
*/

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:

	//How close can the AI tank get to the player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;

private:
///Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

///TICK Functions
	//TICK: TankAIController
	// Called every frame
	virtual void Tick(float DeltaTime) override;

///Variables

};