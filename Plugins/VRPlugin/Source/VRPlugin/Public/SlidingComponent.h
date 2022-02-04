// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRSceneComponent.h"
#include "SlidingComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotGrabbedSignature,AUserController*, UserController);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSlotDroppedSignature,AUserController*, UserController);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderHitMaxPoint);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSliderHitMinPoint);

UCLASS()
class VRPLUGIN_API USlidingComponent : public UVRSceneComponent
{
	GENERATED_BODY()
public:
	//Delegates
	UPROPERTY(BlueprintAssignable)
	FOnSlotGrabbedSignature OnSlotGrabbed;
	UPROPERTY(BlueprintAssignable)
	FOnSlotDroppedSignature OnSlotDropped;
	UPROPERTY(BlueprintAssignable)
	FOnSliderHitMaxPoint OnSliderHitMaxPoint;
	UPROPERTY(BlueprintAssignable)
	FOnSliderHitMinPoint OnSliderHitMinPoint;
	
	//Defaults
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRSliderComponent")
	bool bIsLocked;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRSliderComponent")
	FVector MaxSlideDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VRSliderComponent")
	FVector MinSlideDistance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VRSliderComponent")
	USceneComponent* ComponentToSlide;

	//Variables
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGripped = false;

	//the relative location of slider when component was grabbed useing starting transform 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector InitialGripLoc;

	//the starting transform of sliding component
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform InitialRelativeTransform;
	
	UPROPERTY(BlueprintReadWrite)
	AUserController* GrippingController;

	//relative location of hand from slider on grab location 
	FVector InitialInteractorLocation;
	//slider progress 0 - 1.
	float CurrentSliderProgress;
	float LastSliderProgressState = -1.0f;

	UPROPERTY(BlueprintReadWrite)
	FVector ClampedLocation;

	//functions
	virtual void OnRegister() override;
	virtual void GrabComponent_Implementation(AUserController* UserController) override;
	virtual void DropComponent_Implementation(AUserController* UserController) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void GripTick();
	FVector ClampSlideVector(FVector ValueToClamp);
	float GetCurrentSliderProgress(FVector CurrentLocation);
	void CheckSliderProgress();
	
};


