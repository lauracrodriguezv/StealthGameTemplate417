// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSExtractionZone.h"

#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

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

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComponent"));
	DecalComponent->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComponent->SetupAttachment(RootComponent);
}



void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with extraction zone!"));

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);

	if(IsValid(MyPawn))
	{
		if(MyPawn->bIsCarringObjective)
		{
			AFPSGameMode* GameModeReference = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
			if(GameModeReference)
			{
				GameModeReference->CompleteMission(MyPawn);
			}
		}
		else
		{
			UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
		}
	}

}



