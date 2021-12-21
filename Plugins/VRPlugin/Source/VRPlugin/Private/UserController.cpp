// Fill out your copyright notice in the Description page of Project Settings.


#include "UserController.h"
#include "ComponentUtils.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/Pickupable.h"
#include "PickupableActor.h"



// Sets default values
AUserController::AUserController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	//RootComponent = MotionController;
	MotionController->SetupAttachment(RootComponent);
	MotionController->bDisplayDeviceModel = true;
	
	

	
}


// Called when the game starts or when spawned
void AUserController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUserController::GrabActor(AActor* Actor)
{
	if (Actor == nullptr || !Actor->Implements<UPickupable>()) return;
	auto Pickupable = Cast<IPickupable>(Actor);
	if(!Pickupable->Execute_CanGrabActor(Actor)) return;
		
	bool hasGrabbed = Pickupable->Execute_Grab(Actor, Actor, this); //interface call
	if (hasGrabbed)
	{
		AttachedActor = Actor;
	}
}

void AUserController::DropActor()
{
	if (AttachedActor == nullptr) return;
	
	auto Pickupable = Cast<IPickupable>(AttachedActor);
	bool hasDropped = Pickupable->Execute_Drop(AttachedActor, this);
	if (hasDropped)
	{
		AttachedActor = nullptr;
	}
}


AActor* AUserController::GetClosestActor(TArray<AActor*> OutResults)
{
	float NearestActorDistance = 1000;
	AActor* NearestActor = nullptr;

	for (AActor* Result : OutResults)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, GetDebugName(Result));
		
		if(Cast<IPickupable>(Result))
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("It has casted "));
			float Distance =FVector::Distance(GetActorLocation(), Result->GetActorLocation());
			if(Distance < NearestActorDistance)
			{
				NearestActorDistance = Distance;
				NearestActor = Result;
			}
		}
	
		
	}

	return NearestActor;
	
}

void AUserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bIsHighlightingActor)
	{
		//HighlightActor();
	}
}


void AUserController::EjectPressed()
{
	// if(AttachedActor && Cast<IUsesEject>(AttachedActor))
	// {
	// 	Cast<IUsesEject>(AttachedActor)->Execute_EjectPressed(AttachedActor);
	// }
}

void AUserController::EjectReleased()
{
	// if(AttachedActor && Cast<IUsesEject>(AttachedActor))
	// {
	// 	Cast<IUsesEject>(AttachedActor)->Execute_EjectReleased(AttachedActor);
	// }
}

void AUserController::RumbleController(float Intensity)
{
}

UPrimitiveComponent* AUserController::GetClosestComponent(TArray<UPrimitiveComponent*> Array)
{
	float NearestActorDistance = 1000;
	UPrimitiveComponent* NearestActor = nullptr;
	
	for (UPrimitiveComponent* Result : Array)
	{
		
		if(Cast<IPickupable>(Result))
		{
			float Distance =FVector::Distance(GetActorLocation(), Result->GetComponentLocation());
			if(Distance < NearestActorDistance)
			{
				NearestActorDistance = Distance;
				NearestActor = Result;
			}
		}
	}

	return NearestActor;
}

void AUserController::HandleGrabComponent(UPrimitiveComponent* Component, bool isGrabbing)
{
	if(Component == nullptr) return;
	IPickupable* Pickupable = Cast<IPickupable>(Component);
	if(Pickupable == nullptr ) return;
	

	if (isGrabbing)
	{
		Pickupable->Execute_GrabComponent(Component, this);
	}
	else
	{
		Pickupable->Execute_DropComponent(Component, this);
	}
}



bool AUserController::HighlightActor(float ForwardDistance)
{
	if(HighlightedActor) //if there is a highlighted actor, unhighlight it before highlighting new actor
	{
		auto OldHighlightedActor = Cast<APickupableActor>(HighlightedActor);
		OldHighlightedActor->MeshComponent->SetRenderCustomDepth(false);
		HighlightedActor = nullptr;
	}


	
	FHitResult* Hit = new FHitResult();
	const FVector Forward = MotionController->GetForwardVector();
	FVector Start = MotionController->GetComponentLocation();
	const FVector End = (Forward * ForwardDistance) + Start;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
		
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1);
	if(GetWorld()->LineTraceSingleByChannel(*Hit, Start, End, ECC_Visibility, CollisionQueryParams))
	{
		if(Hit->GetActor() != nullptr)
		{
			if(Hit->GetActor()->Implements<UPickupable>())
			{
				auto Actor = Cast<APickupableActor>(Hit->GetActor());
				Actor->MeshComponent->SetRenderCustomDepth(true);
				HighlightedActor = Hit->GetActor();
				return true;
			}
			
		}
	}
	return false;
}

void AUserController::GrabHighlightedActor()
{
	GrabActor(HighlightedActor);
	if(HighlightedActor) //unhighlight it 
	{
		auto OldHighlightedActor = Cast<APickupableActor>(HighlightedActor);
		OldHighlightedActor->MeshComponent->SetRenderCustomDepth(false);
		HighlightedActor = nullptr;
	}
	
}


void AUserController::Trigger()
{

	// if(AttachedActor && Cast<IUsesTrigger>(AttachedActor))
	// {
	// 	Cast<IUsesTrigger>(AttachedActor)->Execute_TriggerPressed(AttachedActor);
	// 	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Trrigge function"));
	//
	// }
	// else
	// {
	// 	bIsHighlightingActor = true;
	// }
}

void AUserController::TriggerRelease()
{
	/*if(AttachedActor && Cast<IUsesTrigger>(AttachedActor))
	{
		Cast<IUsesTrigger>(AttachedActor)->Execute_TriggerReleased(AttachedActor);
		//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Trrigge function"));

	}

	if(HighlightedActor)
	{
		auto OldHighlightedActor = Cast<APickupableActor>(HighlightedActor);
		OldHighlightedActor->MeshComponent->SetRenderCustomDepth(false);
	}
	
	bIsHighlightingActor = false;*/
}




