// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{

	OverlappingComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappingComponent"));
	OverlappingComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlappingComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlappingComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlappingComponent->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlappingComponent;

	OverlappingComponent->SetHiddenInGame(false);

	OverlappingComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);
}



void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with extraction zone!"));
}



