// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class AFPS_PathActor;

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category= "Components")
	UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);

	UFUNCTION()
	void ResetOrientation();

	UFUNCTION()
	void MoveGuardToNextPatrolPoint();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	bool bIsSeeingPlayer;

	UPROPERTY(EditInstanceOnly)
	bool bPatrol;

	int PatrolPointIndex;

	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition="bPatrol"))
	TArray<AActor*> PathPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI")
	AActor*	CurrentPatrolPoint;

	FRotator OriginalRotation; 

	FTimerHandle TimerHandle_ResetOrientation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:

	UFUNCTION(BlueprintImplementableEvent)
	void BP_MovePlayer();



};
