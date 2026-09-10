// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChairSlot.h"

// Sets default values
APlayerChairSlot::APlayerChairSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up scene components 
	// Trigger collision set up
	triggerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Card Table Slot Trigger Collision"));
	triggerCollision->SetRelativeScale3D(FVector(0.1f, collisionScale, collisionScale));
	this->SetRootComponent(triggerCollision);
	
	// Chair set up
	chair = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Chair"));
	chair->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APlayerChairSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerChairSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlayerChairSlot::GetIsSatIn() const
{
	return bIsSatIn;
}

void APlayerChairSlot::SetIsSatIn(bool bSatBool)
{
	bIsSatIn = bSatBool;
}

