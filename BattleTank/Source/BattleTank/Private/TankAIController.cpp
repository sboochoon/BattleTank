// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "BattleTank.h"
#include "Tank.h"
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
	auto PlayerTank = Cast<ATank>(AActor::GetWorld()->GetFirstPlayerController()->GetPawn());

	//Get the AI tank
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	if (ControlledTank && PlayerTank)
	{
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
}