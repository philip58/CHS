// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"
#include "MainCharacter.h"

// Sets default values
ACardActor::ACardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create card mesh component and set its properties
	cardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	cardMesh->SetRelativeScale3D(FVector(-0.01, 10.0, 14.0));
	this->SetRootComponent(cardMesh);


	// Create card box collision and set its properties
	cardBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Card Box Collision"));
	cardBoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	cardBoxCollision->SetupAttachment(RootComponent);
	//cardBoxCollision->SetRelativeScale3D( FVector(-0.01,0.31,0.44) );
	cardBoxCollision->SetRelativeScale3D( FVector(0.010000, 0.031500, 0.031000) );

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

	if(bIsCardEquipped)
	{
		if (playerCardSocket && this->GetActorLocation() != playerCardSocket->GetComponentLocation())
		{
			this->SetActorLocation(playerCardSocket->GetComponentLocation());
			this->SetActorRotation(playerCardSocket->GetComponentRotation());
		}
	}

}

// Player equip card
void ACardActor::EquipCard(AMainCharacter* playerCharacter)
{
	playerCardSocket = playerCharacter->cardPlaceHolderSocket;

	if (playerCharacter && playerCardSocket)
	{
		UE_LOG(LogTemp, Display, TEXT("Card equipped: %s"), *this->GetName());
		setIsCardEquipped(true);
		owningCharacter = playerCharacter;

		if (cardMesh) cardMesh->SetSimulatePhysics(false);
		if (playerCharacter) this->AttachToComponent(playerCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		this->SetActorLocation(playerCardSocket->GetComponentLocation());
		this->SetActorRotation(playerCardSocket->GetComponentRotation());
	}
}


// Set is equipped boolean
void ACardActor::setIsCardEquipped(bool isEquipped)
{
	bIsCardEquipped = isEquipped;
}



