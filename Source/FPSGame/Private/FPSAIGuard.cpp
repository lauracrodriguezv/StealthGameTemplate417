// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "FPSGameMode.h"
#include "Net/UnrealNetwork.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	PatrolPointIndex = 0;
	bIsSeeingPlayer = false;

	GuardState = EAIState::GuardState_Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation = GetActorRotation();
	MoveGuardToNextPatrolPoint();
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if (IsValid(SeenPawn))
	{
		AFPSGameMode* GameModeReference = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GameModeReference)
		{
			GameModeReference->CompleteMission(SeenPawn, false);
		}

		DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Red, false, 10.0f);
	}

	SetGuardState(EAIState::GuardState_Alerted);	
}

void AFPSAIGuard::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	if (GuardState != EAIState::GuardState_Alerted)
	{
		DrawDebugSphere(GetWorld(), Location, 32.0f, 12.0f, FColor::Green, false, 10.0f);

		FVector Direction = Location - GetActorLocation();
		Direction.Normalize();

		FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewLookAt.Pitch = 0.0f;
		NewLookAt.Roll = 0.0f;

		SetActorRotation(NewLookAt);

		bIsSeeingPlayer = true;

		GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
		GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation, 3.0f);

		SetGuardState(EAIState::GuardState_Suspicious);
	}
}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState != EAIState::GuardState_Alerted)
	{
		bIsSeeingPlayer = false;
		SetActorRotation(OriginalRotation);
		SetGuardState(EAIState::GuardState_Idle);
	}
}

void AFPSAIGuard::MoveGuardToNextPatrolPoint()
{

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

void AFPSAIGuard::OnRep_GuardState()
{
	BP_OnStateChanged(GuardState);
}

void AFPSAIGuard::SetGuardState(EAIState NewGuardState)
{
	if (GuardState == NewGuardState) 
	{
     	return;
    }

	GuardState = NewGuardState;

	OnRep_GuardState();

}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Distance = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
	float GoalDistance = Distance.Size();
	

	//UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	if (GoalDistance <= 100.0 && !bIsSeeingPlayer)
	{
		MoveGuardToNextPatrolPoint();
		//UE_LOG(LogTemp, Warning, TEXT("SimpleMove"));
	}

}

// esta es para replicar en todos los clientes, significa que esta variable va a ser replicada en todos los clientes
void AFPSAIGuard::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AFPSAIGuard, GuardState);
}



