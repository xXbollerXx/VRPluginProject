// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Pickupable.h"
#include "GameFramework/Actor.h"
#include "PickupableActor.generated.h"

UCLASS()
class VRPLUGIN_API APickupableActor : public AActor, public IPickupable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupableActor();
	void AttachToHand(USceneComponent* AttachTo);
	void DetachFromHand();
	
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	bool bCanSimulatePhysics = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanGrabComponents = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bCanBeGrabbed = true;

	UFUNCTION(BlueprintCallable)
	void SetCanBeGrabbed(bool NewCanBeGrabbed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual bool CanGrabActor_Implementation() override;
	virtual bool Grab_Implementation(AActor* Actor, AUserController* UserController) override;
	virtual bool Drop_Implementation(AUserController* UserController) override;

	virtual bool CanGrabComponents_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
