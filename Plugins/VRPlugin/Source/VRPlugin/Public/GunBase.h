// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupableActor.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UENUM()
enum class EFireMode : uint8
{
	Single,
	Burst,
	Auto
};

UCLASS()
class VRPLUGIN_API AGunBase : public APickupableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//components
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UArrowComponent* ProjectileSpawnLoc;

	//defaults
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunDefaults")
	EFireMode FireMode = EFireMode::Single;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunDefaults")
	float RateOfAutoFire = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunDefaults")
	bool bHasUnlimitedAmmo = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunDefaults")
	bool bIsTwoHanded = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GunDefaults")
	bool bNeedsTwoHands = false;

	UPROPERTY(EditDefaultsOnly, Category = "GunDefaults")
	TSubclassOf<UDamageType> DamageTypeClass;

	//cosmetics
	UPROPERTY(EditDefaultsOnly, Category="GunDefaults")
	UParticleSystem* MuzzelFlashTemplate;

	UPROPERTY(EditDefaultsOnly, Category = "GunDefaults")
	TSubclassOf<AActor> BulletCasingTemplate;

	//variables 
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* AttachedHand;
	
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* OtherHand;

	//UPROPERTY()
	//AMagActor* AttachedMag;
	
	UPROPERTY(BlueprintReadWrite)
	bool bGunPrimed = false;

	//functions
	UFUNCTION(BlueprintCallable)
	void Fire(AController* EventInstigator, float Distance = 10000);

	UFUNCTION(BlueprintCallable)
	void SpawnFireCosmetics(UPrimitiveComponent* CasingSpawnLoc);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
