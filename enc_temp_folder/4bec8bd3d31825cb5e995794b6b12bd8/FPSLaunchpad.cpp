// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchpad.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSLaunchpad::AFPSLaunchpad()
{
	LaunchpadMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Launchpad Mesh"));
	RootComponent = LaunchpadMeshComponent;

	OverlappingComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlappingComponent"));
	OverlappingComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlappingComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlappingComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlappingComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	OverlappingComponent->SetBoxExtent(FVector(200.0f));
	OverlappingComponent->SetupAttachment(LaunchpadMeshComponent);

	OverlappingComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchpad::ActiveLaunchpad); 

	launchpadImpulse = FVector(0.0f, 0.0f, 1000.0f);
}

void AFPSLaunchpad::ActiveLaunchpad(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor))
	{
		return;
	}

	AFPSCharacter* OverlappedCharacter = Cast<AFPSCharacter>(OtherActor);
	if (IsValid(OverlappedCharacter))
	{
		OverlappedCharacter->LaunchCharacter(launchpadImpulse, false, true);
	} 		

	if(IsValid(OtherComp) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(launchpadImpulse, NAME_None, true);
	}

	UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());

}
