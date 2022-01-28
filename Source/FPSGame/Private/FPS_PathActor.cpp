// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_PathActor.h"
#include "Components/BillboardComponent.h"

// Sets default values
AFPS_PathActor::AFPS_PathActor()
{
 	
	PathBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("PathBillboard"));
	RootComponent = PathBillboardComponent;

}

// Called when the game starts or when spawned
void AFPS_PathActor::BeginPlay()
{
	Super::BeginPlay();
	
}



