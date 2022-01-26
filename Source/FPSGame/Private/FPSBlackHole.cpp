// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"


// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HoleMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoleMeshComp"));
	HoleMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = HoleMeshComp;

	AttractSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("AttractSphereComp"));
	AttractSphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttractSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttractSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	AttractSphereComp->SetSphereRadius(1000.0f);
	AttractSphereComp->SetupAttachment(HoleMeshComp);


	DestroySphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphereComp"));
	DestroySphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DestroySphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroySphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	DestroySphereComp->SetupAttachment(HoleMeshComp);

	
	RadiusBlackHole = 1000.0f;
	AttractStrength = -2000.0f;
}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	DestroySphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::BlackHoleDestroy);
}


void AFPSBlackHole::Attract()
{
	for (UPrimitiveComponent* Component : OverlappingComp)
	{
		Component->AddRadialForce(this->GetActorLocation(), RadiusBlackHole, AttractStrength, ERadialImpulseFalloff::RIF_Constant, true);
	}
}

void AFPSBlackHole::BlackHoleDestroy(class UPrimitiveComponent* const OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();

}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AttractSphereComp->GetOverlappingComponents(OverlappingComp);

	if (OverlappingComp.Num() > 0)
	{
		Attract();
	}
}

