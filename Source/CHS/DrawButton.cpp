// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawButton.h"

// Sets default values
ADrawButton::ADrawButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components and set root/attachments
	boxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Draw Button Box Collision"));
	buttonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Draw Button Mesh Component"));

	this->SetRootComponent(boxCollisionComponent);
	buttonMeshComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADrawButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADrawButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

