// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSLaunchpad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPSLaunchpad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSLaunchpad();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* LaunchpadMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* OverlappingComponent;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	FVector launchpadImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* LaunchFX;

protected:

	UFUNCTION()
	void ActiveLaunchpad(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
