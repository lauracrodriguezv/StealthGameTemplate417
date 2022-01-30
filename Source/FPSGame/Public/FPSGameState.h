// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()
	

public:

//NetMulticast significa quer si esta funcion es llamada desde el server it gets sent to all clients, incluido el servidor
    UFUNCTION(NetMulticast, Reliable)
    void MulticastOnMissionComplete(APawn* InstigatorPawn, bool bMissionSuccess);


};
