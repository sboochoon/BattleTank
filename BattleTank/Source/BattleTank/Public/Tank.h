// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


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

private:	
///Functions
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;					
};