// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserController.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "VRPawn.generated.h"

UCLASS(HideCategories =(Replecation))
class VRPLUGIN_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RotatePlayerPawn(float AxisValue);
	
	UFUNCTION(BlueprintCallable)
	void MovePlayerPawnForwardAxis(float AxisValue);
	
	UFUNCTION(BlueprintCallable)
	void MovePlayerPawnRightAxis(float AxisValue);

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* VROrigin;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AUserController> UserControllerClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};



