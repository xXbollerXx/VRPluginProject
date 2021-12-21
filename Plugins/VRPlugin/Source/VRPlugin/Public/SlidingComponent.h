// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRSceneComponent.h"
#include "SlidingComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotGrabbedSignature,AUserController*, UserController);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotDroppedSignature,AUserController*, UserController);

UCLASS()
class VRPLUGIN_API USlidingComponent : public UVRSceneComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FOnSlotGrabbedSignature OnSlotGrabbed;
	UPROPERTY(BlueprintAssignable)
	FOnSlotDroppedSignature OnSlotDropped;
	
	virtual void GrabComponent_Implementation(AUserController* UserController) override;
	virtual void DropComponent_Implementation(AUserController* UserController) override;
};
