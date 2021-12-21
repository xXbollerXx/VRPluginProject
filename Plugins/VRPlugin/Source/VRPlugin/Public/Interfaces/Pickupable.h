// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UserController.h"
#include "Pickupable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VRPLUGIN_API IPickupable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanGrabActor();
	
	/// pram1 MotionController parm2 object to attach implementation to Returns true if it has been attached
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Grab(AActor* Actor, AUserController* UserController); 
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool Drop(AUserController* UserController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool CanGrabComponents();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void GrabComponent(AUserController* UserController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DropComponent(AUserController* UserController);
	
};
