// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

/**
*
*/

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
///Functions
/*Constructor*/
	// Sets default values for this pawn's properties
	AProjectile();

	// Movement of projectile
	void LaunchProjectile(float Speed);

///TICK Functions
	// TICK: Projectile
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
///Functions
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
///Variables
	// Variable type for projectile movement: https://docs.unrealengine.com/latest/INT/API/Runtime/Engine/GameFramework/UProjectileMovementComponent/
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
};