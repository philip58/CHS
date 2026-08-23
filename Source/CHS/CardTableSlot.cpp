// Fill out your copyright notice in the Description page of Project Settings.


#include "CardTableSlot.h"

// Sets default values
ACardTableSlot::ACardTableSlot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set actor properties and attach to root
	triggerCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Card Table Slot Trigger Collision"));
	triggerCollision->SetRelativeScale3D(FVector(0, collisionScale, collisionScale));
	triggerCollision->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ACardTableSlot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardTableSlot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

