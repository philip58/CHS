// Fill out your copyright notice in the Description page of Project Settings.


#include "CardActor.h"
#include "CardTableSlot.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"

// Sets default values
ACardActor::ACardActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create card mesh component and set its properties
	cardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Mesh"));
	cardMesh->SetRelativeScale3D(FVector(.2, .2, .2));
	/*this->SetRootComponent(cardMesh);*/


	// Create card box collision and set its properties
	cardBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Card Box Collision"));
	cardBoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	//cardBoxCollision->SetupAttachment(RootComponent);
	cardBoxCollision->SetRelativeScale3D( FVector(0.05,1.5625,2.2125) );

	this->SetRootComponent(cardBoxCollision);
	cardMesh->SetupAttachment(RootComponent);

	cardBoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACardActor::OnBeginOverlap);


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

// Player equip card, attach to player card socket and remove collision channel
void ACardActor::EquipCard(AMainCharacter* playerCharacter)
{
	playerCardSocket = playerCharacter->cardPlaceHolderSocket;

	if (playerCharacter && playerCardSocket)
	{
		SetIsCardEquipped(true);
		owningCharacter = playerCharacter;

		if (cardMesh) cardMesh->SetSimulatePhysics(false);
		if (cardBoxCollision) cardBoxCollision->SetSimulatePhysics(false);
		if (playerCharacter) this->AttachToComponent(playerCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		this->SetActorLocation(playerCardSocket->GetComponentLocation());
		this->SetActorRotation(playerCardSocket->GetComponentRotation());
		cardBoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		cardMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		cardBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

// Player unequip card, add collision channel back 
void ACardActor::UnequipCard()
{
	cardBoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	cardMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	cardBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Set is equipped boolean
void ACardActor::SetIsCardEquipped(const bool& isEquipped)
{
	bIsCardEquipped = isEquipped;
}

// Collision overlap method for card placing on table slot
void ACardActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Return if card is equipped
	if (bIsCardEquipped)
	{
		return;
	}

	// If no overlap, return
	if (!IsValid(OtherComp))
	{
		return;
	}

	// Check if other component is a table slot. If it is, set card in the slot
	AActor* compActor = OtherComp->GetOwner();
	if (compActor && compActor->IsA(ACardTableSlot::StaticClass()) )
	{
		PlaceCardInTableSlot(compActor);
	}

}

void ACardActor::PlaceCardInTableSlot(AActor* actor)
{
	this->SetActorRelativeRotation(actor->GetActorRotation() + FRotator(180, 0, 0));
	this->SetActorLocation(actor->GetActorLocation() + FVector(0, 0, tableSlotVertOffset));
	cardBoxCollision->SetSimulatePhysics(false);
	cardBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Set cards new mesh
void ACardActor::SetCardMesh(UStaticMesh* newCardMesh)
{
	if (cardMesh && newCardMesh)
	{
		cardMesh->SetStaticMesh(newCardMesh);
	}
}

// Set the card type
void ACardActor::SetCardType(const ECardType& newCardType)
{
	cardType = newCardType;
}

// Set the card value
void ACardActor::SetCardValue(const ECardValue& newCardValue)
{
	cardValue = newCardValue;
}

// Get the card type
ECardType ACardActor::GetCardType() const
{
	return cardType;
}

// Get the card value
ECardValue ACardActor::GetCardValue() const
{
	return cardValue;
}

