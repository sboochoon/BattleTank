// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"


/* AProjectile Constructor
Sets default values
*/
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//CreateDefaultSubobject<Class>(FName("NAME")) adds a component of <Class> with NAME by default to the actor
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));

	//Turn off this component by default since we will activate it ourselves in the LaunchProjectile function
	ProjectileMovementComponent->bAutoActivate = false;
}


/* BeginPlay
Called when the game starts or when spawned
*/
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

/* Tick
TICK: Called every tick via Projectile
*/
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/* LaunchProjectile
Movement of projectile
*/
void AProjectile::LaunchProjectile(float Speed)
{
	//Perform projectile movement commands
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);

	//Activate projectile
	ProjectileMovementComponent->Activate();
}