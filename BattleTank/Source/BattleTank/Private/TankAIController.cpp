// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlled Tank ID: %s"), *ControlledTank->GetName());
	}

	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI did not find Player"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Found Player, ID: %s"), *PlayerTank->GetName());
	}

}



ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = Cast<ATank>(AActor::GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerPawn) { return nullptr;}

	return PlayerPawn;
}


