// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGunBase::Fire(AController* EventInstigator, float Distance)
{
	//raycast for world statics
	FHitResult* Hit = new FHitResult();
	const FVector Forward = ProjectileSpawnLoc->GetForwardVector();
	FVector Start = ProjectileSpawnLoc->GetComponentLocation();
	const FVector End = (Forward * Distance) + Start;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
		
	if(GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility, CollisionQueryParams))
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1);
		if(Hit->GetActor() != nullptr)
		{
			//hit location emitter
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzelFlashTemplate, Hit->Location, Hit->Normal.Rotation(), ProjectileSpawnLoc->GetComponentScale());

			UGameplayStatics::ApplyDamage(Hit->GetActor(), 10, EventInstigator, this, DamageTypeClass);
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzelFlashTemplate, ProjectileSpawnLoc->GetComponentLocation(),ProjectileSpawnLoc->GetComponentRotation() , ProjectileSpawnLoc->GetComponentScale());


}

void AGunBase::SpawnFireCosmetics(UPrimitiveComponent* CasingSpawnLoc)
{
	// art stuff
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzelFlashTemplate, ProjectileSpawnLoc->GetComponentLocation(),ProjectileSpawnLoc->GetComponentRotation() , ProjectileSpawnLoc->GetComponentScale());

		
	FActorSpawnParameters SpawnParameters;
	//SpawnParameters.Name = TEXT("BulletCasing");
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto Casing = GetWorld()->SpawnActor<AActor>(BulletCasingTemplate, CasingSpawnLoc->GetComponentLocation(), CasingSpawnLoc->GetComponentRotation(), SpawnParameters);

}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

