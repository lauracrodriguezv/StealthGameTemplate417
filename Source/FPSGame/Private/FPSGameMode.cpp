// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "FPSGameState.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionComplete)
{
	if(InstigatorPawn)
	{
		if(IsValid(SpectatingViewPointClass))
		{ 
			TArray<AActor*> SpectatingCamerasActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewPointClass, SpectatingCamerasActors);

			if (SpectatingCamerasActors.Num() > 0)
			{
				AActor* NewViewTarget = SpectatingCamerasActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PlayerController = It->Get();
					if (PlayerController)
					{
						PlayerController->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			 UE_LOG(LogTemp, Warning, TEXT("SpectatingViewPointClass is nullptr, Please update GameMode class with valid subclass. Cannot change spectating view target"));
		}

	}	

	AFPSGameState* GameStateReference = GetGameState<AFPSGameState>();
	if (GameStateReference)
	{
		GameStateReference->MulticastOnMissionComplete(InstigatorPawn, bMissionComplete);
	}
}	