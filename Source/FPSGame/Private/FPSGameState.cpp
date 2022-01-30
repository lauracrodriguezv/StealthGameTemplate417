// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
    {
        AFPSPlayerController* PlayerControllerReference = Cast<AFPSPlayerController>(It->Get());
        if (IsValid(PlayerControllerReference) && PlayerControllerReference->IsLocalController())
        {
            PlayerControllerReference->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

            APawn* PawnReference = PlayerControllerReference->GetPawn();
            if (PawnReference)
            {
                PawnReference->DisableInput(nullptr);
            }
        }
    }
}
