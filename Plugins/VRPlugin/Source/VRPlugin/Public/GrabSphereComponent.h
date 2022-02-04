// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Interfaces/Pickupable.h"
#include "GrabSphereComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSphereGrabbedSignature,AUserController*, UserController);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSphereDroppedSignature,AUserController*, UserController);


/**
 * 
 */
UCLASS(Blueprintable)
class VRPLUGIN_API UGrabSphereComponent : public USphereComponent, public IPickupable
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSphereGrabbedSignature OnSphereGrabbed;
	UPROPERTY(BlueprintAssignable)
	FOnSphereDroppedSignature OnSphereDropped;
	
	virtual void GrabComponent_Implementation(AUserController* UserController) override;
	virtual void DropComponent_Implementation(AUserController* UserController) override;
};
