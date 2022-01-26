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
	AttractSphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttractSphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttractSphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	AttractSphereComp->SetupAttachment(HoleMeshComp);

	DestroySphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphereComp"));
	DestroySphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	DestroySphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	DestroySphereComp->SetupAttachment(HoleMeshComp);

	

}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
	
	AttractSphereComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::Attract);
}

void AFPSBlackHole::Attract(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(OtherComp))
	{
		//OtherComp->AddRadialForce(this->GetActorLocation(), )
	}
}

void AFPSBlackHole::Destroy(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

