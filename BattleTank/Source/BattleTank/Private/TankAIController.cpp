// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

/* BeginPlay
Called when the game starts or when spawned
*/
void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

/* Tick
TICK: Called every tick via TankAIController
*/
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Get the player tank
	auto PlayerTank = AActor::GetWorld()->GetFirstPlayerController()->GetPawn();

	//Get the AI tank
	auto ControlledTank = GetPawn();

	//Get the AI tank aiming component
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (!ensure(AimingComponent)) { return; }

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim at player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//If locked then fire
	if (AimingComponent->GetFiringState() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}