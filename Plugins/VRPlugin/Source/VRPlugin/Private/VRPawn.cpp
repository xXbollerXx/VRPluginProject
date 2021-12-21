// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "MotionControllerComponent.h"
#include "Camera/CameraComponent.h"



// Sets default values
AVRPawn::AVRPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
    VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(Root);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(VROrigin);
	

}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, "ffffffffffffffffffffffffff");

	/*
	//motion controller spawn parameters
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//left motion controller setup
	SpawnParameters.Name = FName(TEXT("LeftMotionController"));
	LeftMotionController = GetWorld()->SpawnActor<AUserController>(SpawnParameters);
	LeftMotionController->AttachToComponent(VROrigin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	LeftMotionController->ControllerHand = EControllerHand::Left;
	LeftMotionController->MotionController->MotionSource = FName(TEXT("Left"));
	LeftMotionController->SetupControls(Cast<APlayerController>(GetController()));

	//right motion controller setup
	SpawnParameters.Name = FName(TEXT("RightMotionController"));
	RightMotionController = GetWorld()->SpawnActor<AUserController>(SpawnParameters);
	RightMotionController->AttachToComponent(VROrigin, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	RightMotionController->ControllerHand = EControllerHand::Right;
	RightMotionController->MotionController->MotionSource = FName(TEXT("Right"));
	RightMotionController->SetupControls(Cast<APlayerController>(GetController()));
	*/
    
}

void AVRPawn::RotatePlayerPawn(float AxisValue)
{
	AddActorWorldRotation(FRotator(0,AxisValue, 0));
}

void AVRPawn::MovePlayerPawnForwardAxis(float AxisValue)
{
	auto Temp = FVector::VectorPlaneProject(CameraComponent->GetForwardVector(), FVector(0,0,1));
	Temp *= AxisValue;
	AddActorWorldOffset(Temp);

}

void AVRPawn::MovePlayerPawnRightAxis(float AxisValue)
{
	auto Temp = FVector::VectorPlaneProject(CameraComponent->GetRightVector(), FVector(0,0,1));
	Temp *= AxisValue;
	AddActorWorldOffset(Temp);
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


