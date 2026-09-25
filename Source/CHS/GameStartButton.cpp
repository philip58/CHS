// Fill out your copyright notice in the Description page of Project Settings.


#include "GameStartButton.h"
#include "Components/BoxComponent.h"

// Sets default values
AGameStartButton::AGameStartButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create components and set root/attachments
	boxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Start Button Box Collision"));
	buttonMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Start Button Mesh Component"));

	this->SetRootComponent(boxCollisionComponent);
	buttonMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGameStartButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameStartButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Return the bGameHasStarted boolean
bool AGameStartButton::GetGameHasStarted() const
{
	return bHasGameStarted;
}

// Set bHasGameStarted boolean
void AGameStartButton::SetGameHasStarted(const bool& gameStarted)
{
	bHasGameStarted = gameStarted;
}

