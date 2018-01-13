// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LineTraceRange = 100000.0f;

private:
	//Start moving the barrel toward the crosshair UI in the world
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector& OutHit, FVector LookDirection) const;
	


};
