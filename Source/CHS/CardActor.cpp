// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"

// Sets default values
ACardActor::ACardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create card mesh component
	cardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	cardMesh->SetupAttachment(RootComponent);
	cardMesh->SetRelativeScale3D(FVector(-0.01, 10.0, 14.0));

	// Create card box collision and set its properties
	cardBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Card Box Collision"));
	cardBoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	cardBoxCollision->SetupAttachment(RootComponent);
	cardBoxCollision->SetRelativeScale3D( FVector(-0.01,0.31,0.44) );
}

// Called when the game starts or when spawned
void ACardActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACardActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

