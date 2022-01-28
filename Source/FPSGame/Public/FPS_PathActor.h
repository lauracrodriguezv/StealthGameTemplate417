// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_PathActor.generated.h"

UCLASS()
class FPSGAME_API AFPS_PathActor : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBillboardComponent* PathBillboardComponent;

public:	
	// Sets default values for this actor's properties
	AFPS_PathActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
