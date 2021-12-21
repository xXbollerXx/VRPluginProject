// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupableActor.h"

#include "Algo/Rotate.h"

// Sets default values
APickupableActor::APickupableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(false);
	
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//MeshComponent->SetupAttachment(Root);
	RootComponent = MeshComponent;

	
}

void APickupableActor::SetCanBeGrabbed(bool NewCanBeGrabbed)
{
	bCanBeGrabbed = NewCanBeGrabbed;
}

// Called when the game starts or when spawned
void APickupableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool APickupableActor::CanGrabActor_Implementation()
{
	return bCanBeGrabbed;
}

bool APickupableActor::Grip_Implementation(AActor* Actor, AUserController* UserController)
{
	SetCanBeGrabbed(false);
	AttachToHand(UserController->MotionController);
	return true;
}

bool APickupableActor::Drop_Implementation(AUserController* UserController)
{
	SetCanBeGrabbed(true);
	DetachFromHand();
	return true;
}

bool APickupableActor::CanGrabComponents_Implementation()
{
	return bCanGrabComponents;
}



void APickupableActor::AttachToHand(USceneComponent* AttachTo)
{
	
	MeshComponent->SetSimulatePhysics(false);
	AttachToComponent(AttachTo, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Snap"));
}

void APickupableActor::DetachFromHand()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if(bCanSimulatePhysics)
	{
		MeshComponent->SetSimulatePhysics(true);
	}
}

// Called every frame
void APickupableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

