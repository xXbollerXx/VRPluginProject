// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabSphereComponent.h"

void UGrabSphereComponent::GrabComponent_Implementation(AUserController* UserController)
{
	OnSphereGrabbed.Broadcast(UserController);
}

void UGrabSphereComponent::DropComponent_Implementation(AUserController* UserController)
{
	OnSphereDropped.Broadcast(UserController);
}
