// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingComponent.h"

#include "DrawDebugHelpers.h"

void USlidingComponent::OnRegister()
{
	Super::OnRegister();
	InitialRelativeTransform = this->GetRelativeTransform();

}

void USlidingComponent::GrabComponent_Implementation(AUserController* UserController)
{
	GrippingController = UserController;
	
	
	FTransform CurrentRelativeTransform = GetRelativeTransform();// get slider relative trans from parent component trans
	InitialInteractorLocation = CurrentRelativeTransform.InverseTransformPosition(UserController->MotionController->GetComponentLocation());
	
	InitialGripLoc = InitialRelativeTransform.InverseTransformPosition(this->GetRelativeLocation()); 
	//InitialGripLoc = UserController->GetActorLocation();
	bIsGripped = true;
	LastSliderProgressState = -1.0f;

}

void USlidingComponent::DropComponent_Implementation(AUserController* UserController)
{
	Super::DropComponent_Implementation(UserController);
}

void USlidingComponent::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	if (bIsGripped)
	{
		GripTick();
	}
	else
	{
		
	}
}

void USlidingComponent::GripTick()
{
	FTransform CurrentRelativeTransform = GetRelativeTransform();
	//current location of hand relative to parent component 
	FVector CurInteractorLocation = CurrentRelativeTransform.InverseTransformPosition(GrippingController->MotionController->GetComponentLocation());
	//location of slider using offset calculated from hand start and current location
	FVector CalculatedLocation = InitialGripLoc + (CurInteractorLocation - InitialInteractorLocation);
	DrawDebugSphere(GetWorld(), GetOwner()->GetTransform().TransformPosition(CalculatedLocation), 5.0f, 6, FColor::Red, false, 0.1f, 0);

	//follow spline
	//else

	 ClampedLocation = ClampSlideVector(CalculatedLocation);
	this->SetRelativeLocation(InitialRelativeTransform.TransformPosition(ClampedLocation));
	CurrentSliderProgress = GetCurrentSliderProgress(ClampedLocation);

	CheckSliderProgress();

	ComponentToSlide->SetRelativeLocation(ClampedLocation);
	//auto drop
	
}

FVector USlidingComponent::ClampSlideVector(FVector ValueToClamp)
{


	FVector Dist = MinSlideDistance + MaxSlideDistance;
	FVector Progress = (ValueToClamp - (-MinSlideDistance)) / Dist;


	Progress.X = FMath::Clamp(Progress.X, 0.f, 1.f);
	Progress.Y = FMath::Clamp(Progress.Y, 0.f, 1.f);
	Progress.Z = FMath::Clamp(Progress.Z, 0.f, 1.f);

	return (Progress * Dist) - (MinSlideDistance);

}

float USlidingComponent::GetCurrentSliderProgress(FVector CurrentLocation)
{
	float Progress = 0.f;
	Progress = FMath::Clamp(FVector::Dist(-MinSlideDistance, CurrentLocation) / FVector::Dist(-MinSlideDistance, MaxSlideDistance), 0.0f, 1.0f);
	return Progress;

}
 void USlidingComponent::CheckSliderProgress()
{
	// Skip first check, this will skip an event throw on rounded
	if (LastSliderProgressState < 0.0f)
	{
		// Skip first tick, this is our resting position
		LastSliderProgressState = CurrentSliderProgress;
	}
	else if (CurrentSliderProgress == 1.0f)
	{
		OnSliderHitMaxPoint.Broadcast();
	}
	else if (CurrentSliderProgress == 0.0f)
	{
		OnSliderHitMinPoint.Broadcast();

	}
}
