// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerChairSlot.h"
#include "Components/TextRenderComponent.h"

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

	// Set up text component
	textComponent = CreateDefaultSubobject<UTextRenderComponent>("Chair Text Component");
	textComponent->SetupAttachment(RootComponent);
	textComponent->SetRelativeLocation(this->GetActorLocation() + FVector(chairTextXPadding, chairTextYPadding, chairTextZPadding));
	textComponent->SetRelativeRotation(FRotator(0,90,-90));
	textComponent->SetText(FText::FromString(""));
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

// Get the character sitting in the chair
TObjectPtr<AMainCharacter> APlayerChairSlot::GetCharacterInChair() const
{
	return characterInChair;
}

// Set the character sitting in the chair
void APlayerChairSlot::SetCharacterInChair(TObjectPtr<AMainCharacter> character)
{
	characterInChair = character;
}

// Set the player chair text
void APlayerChairSlot::SetChairText(const FString& str)
{
	// Return if no text component
	if (!textComponent) return;

	textComponent->SetText(FText::FromString(str));
}

// Highlight chair text when it's the player's turn
void APlayerChairSlot::HighlightChairText()
{
	if (!highlightMaterial || !textComponent) return;
	textComponent->SetTextMaterial(highlightMaterial);
}

// Unhighlight chair text when it's not the player's turn
void APlayerChairSlot::UnHighlightChairText()
{
	if (!unHighlightMaterial || !textComponent) return;
	textComponent->SetTextMaterial(unHighlightMaterial);
}
