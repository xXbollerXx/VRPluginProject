// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "ControllerComponent.h"
#include "MotionControllerComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "UserController.generated.h"
class AUserController;


USTRUCT(BlueprintType)
	struct FHandInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	AActor* AttachedActor;
	
	UPROPERTY(BlueprintReadWrite)
	AUserController* UserController;

	UPROPERTY(BlueprintReadWrite)
	AUserController* OtherUserController;


	
};

UCLASS(BlueprintType)
class VRPLUGIN_API AUserController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUserController();
	
	void SetupControls(APlayerController* Controller);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite) 
	AActor* AttachedActor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UMotionControllerComponent* MotionController;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite) 
	AActor* HighlightedActor;
	
	UPROPERTY(BlueprintReadWrite) 
	bool bIsHighlightingActor = false;
	
	UFUNCTION(BlueprintCallable)
	bool HighlightActor(float ForwardDistance = 1000);
	
	UFUNCTION(BlueprintCallable)
	void GrabHighlightedActor();
	
	void Trigger();
	void TriggerRelease();

	void EjectPressed();
	void EjectReleased();

	UFUNCTION(BlueprintCallable)
	void GrabActor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	void DropActor();
	
	UFUNCTION(BlueprintCallable)
	AActor* GetClosestActor(TArray<AActor*> OutResults);
	
	UFUNCTION(BlueprintCallable)
	void RumbleController(float Intensity = 0.7f);

	UFUNCTION(BlueprintCallable)
	UPrimitiveComponent* GetClosestComponent(TArray<UPrimitiveComponent*> Array);

	UFUNCTION(BlueprintCallable)
	void HandleGrabComponent(UPrimitiveComponent* Component, bool isGrabbing);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
