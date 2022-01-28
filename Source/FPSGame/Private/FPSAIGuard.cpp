// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	OriginalRotation = GetActorRotation();

	PatrolPointIndex = 0;
	bIsSeeingPlayer = false;
	
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	
	MoveGuardToNextPatrolPoint();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (SeenPawn == nullptr)
	{
		return;
	}
	
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	bIsSeeingPlayer = true;

	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);
}

void AFPSAIGuard::ResetOrientation()
{
	SetActorRotation(OriginalRotation);
	bIsSeeingPlayer = false;
}

void AFPSAIGuard::MoveGuardToNextPatrolPoint()
{
	if (bIsSeeingPlayer == true)
	{
	    return;
	}

	if (IsValid(CurrentPatrolPoint))
	{
		CurrentPatrolPoint = PathPoints[PatrolPointIndex];
		BP_MovePlayer();
	}

	if (PatrolPointIndex >= PathPoints.Num()-1)
	{
		PatrolPointIndex = 0;
	}
	else 
	{
		PatrolPointIndex++;
	}
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Distance = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
	float GoalDistance = Distance.Size();
	

	//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	if (GoalDistance <= 100.0)
	{
		MoveGuardToNextPatrolPoint();
		//UE_LOG(LogTemp, Warning, TEXT("SimpleMove"));
	}

}



