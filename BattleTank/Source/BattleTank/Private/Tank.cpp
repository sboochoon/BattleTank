// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

/* ATank Constructor
Sets default values
*/
ATank::ATank()
{
 	// We don't need the Tank to tick every frame
	PrimaryActorTick.bCanEverTick = false;
}

/* SetupPlayerInputComponent
Called to bind functionality to input
*/
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}