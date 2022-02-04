// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Interfaces/Pickupable.h"
#include "VRSceneComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class VRPLUGIN_API UVRSceneComponent : public USceneComponent, public IPickupable
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVRSceneComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GrabComponent_Implementation(AUserController* UserController) override;
	virtual void DropComponent_Implementation(AUserController* UserController) override;
		
};
