// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CardActor.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up player camera and its properties: Create component, attach to root, use pawn rotation
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	playerCamera->SetupAttachment(RootComponent);
	playerCamera->bUsePawnControlRotation = true;

	// Set up card placeholder socket and properties: location, rotation
	cardPlaceHolderSocket = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Socket"));
	cardPlaceHolderSocket->SetupAttachment(RootComponent);
	cardPlaceHolderSocket->SetRelativeLocation(FVector(75.0, 0.0, 40.0));
	cardPlaceHolderSocket->SetRelativeRotation(FRotator(-20.0, 0.0, 0.0));

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Get temporary world variable and use it to set the gamemode base to the custom MainGameModeBase
	TWeakObjectPtr<UWorld> tempWorld = GetWorld();
	if (tempWorld != nullptr)
	{
		try
		{
			gameModeBase = Cast<AMainGameModeBase>(tempWorld->GetAuthGameMode());
		}
		catch (const std::exception&)
		{
			UE_LOG(LogTemp, Display, TEXT("Casting gamemode to AMainGameMode failed"));
		}
	}
	
	if (gameModeBase)
	{
		// Set up player movement properties: default speed 
		gameModeBase->playerMovementComponent->MaxWalkSpeed = walkSpeed;
		gameModeBase->playerMovementComponent->AirControl = airControl;
	}

	if (cardPlaceHolderSocket)
	{
		cardPlaceHolderSocket->SetVisibility(false);
		cardPlaceHolderSocket->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	
}

// Called every frame
void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	// Bind axis mappings (walk up, walk down, walk left, walk right, look vertically, look horizontally)
	playerInputComponent->BindAxis("WalkForward", this, &AMainCharacter::WalkForward);
	playerInputComponent->BindAxis("WalkBackwards", this, &AMainCharacter::WalkBackwards);
	playerInputComponent->BindAxis("WalkLeft", this, &AMainCharacter::WalkLeft);
	playerInputComponent->BindAxis("WalkRight", this, &AMainCharacter::WalkRight);
	playerInputComponent->BindAxis("LookHorizontally", this, &AMainCharacter::LookHorizontally);
	playerInputComponent->BindAxis("LookVertically", this, &AMainCharacter::LookVertically);

	// Bind action mappings (jump, sprint, interact, throw, scroll up/down, toggle inventory)
	playerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainCharacter::PlayerJump);
	playerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMainCharacter::StartSprinting);
	playerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMainCharacter::StopSprinting);
	playerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &AMainCharacter::Interact);
	playerInputComponent->BindAction("Throw", EInputEvent::IE_Released, this, &AMainCharacter::Throw);
	playerInputComponent->BindAction("ScrollUp", EInputEvent::IE_Pressed, this, &AMainCharacter::ScrollUp);
	playerInputComponent->BindAction("ScrollDown", EInputEvent::IE_Pressed, this, &AMainCharacter::ScrollDown);
	playerInputComponent->BindAction("ToggleInventory", EInputEvent::IE_Pressed, this, &AMainCharacter::ToggleInventory); 
}

// Move the player forward
void AMainCharacter::WalkForward(float input )
{
	AddMovementInput(GetActorForwardVector(), input);
}

// Move the player backwards
void AMainCharacter::WalkBackwards(float input)
{
	AddMovementInput(GetActorForwardVector(), -input);
}

// Move the player left
void AMainCharacter::WalkLeft(float input)
{
	AddMovementInput(GetActorRightVector(), -input);
}

// Move the player right
void AMainCharacter::WalkRight(float input)
{
	AddMovementInput(GetActorRightVector(), input);
}

// Player jump
void AMainCharacter::PlayerJump()
{
	if(CanJump())
	{
		Jump();
	}
}

// Player looking left and right
void AMainCharacter::LookHorizontally(float input)
{
	AddControllerYawInput(input);
}

// Player looking up and down
void AMainCharacter::LookVertically(float input)
{
	AddControllerPitchInput(-input);
}

// Make the player faster if sprinting
void AMainCharacter::StartSprinting()
{
	//bIsPlayerSprinting = true;
	if (gameModeBase)
	{
		gameModeBase->playerMovementComponent->MaxWalkSpeed = sprintSpeed;
	}
}

// Make the player slower if not sprinting
void AMainCharacter::StopSprinting()
{
	//bIsPlayerSprinting = false;
	if (gameModeBase)
	{
		gameModeBase->playerMovementComponent->MaxWalkSpeed = walkSpeed;
	}
}

// Handle player interaction (E key) 
void AMainCharacter::Interact()
{
	// Game mode base is necessary for getting the stored player/world variables
	if (!gameModeBase)
	{
		return;
	}

	// Initialize helper variables for line tracing and collision handling 
	FHitResult hitResult;
	FVector forwardVector = playerCamera->GetForwardVector();
	FVector cameraLocation = playerCamera->GetComponentLocation();
	
	// Draw the line trace and check what was hit
	DrawDebugLine
	(
		gameModeBase->playerWorld, 
		cameraLocation + (forwardVector * FVector(lineTraceStartOffset, lineTraceStartOffset, lineTraceStartOffset)), 
		cameraLocation + forwardVector * FVector(lineTraceLength, lineTraceLength, lineTraceLength), 
		FColor::Cyan, true, 5.0);
	
	// Line trace to see if the player is looking directly at something that they can interact with
	gameModeBase->playerWorld->LineTraceSingleByChannel
	(
		hitResult, 
		cameraLocation + ( forwardVector * FVector(lineTraceStartOffset, lineTraceStartOffset, lineTraceStartOffset)), 
		cameraLocation + (forwardVector * FVector(lineTraceLength, lineTraceLength, lineTraceLength)), 
		ECollisionChannel::ECC_Visibility
	);

	// Helper variables
	UPrimitiveComponent* hitComponent;
	AActor* hitActor;
	ACardActor* card;
	hitComponent = hitResult.GetComponent();

	// Return if nothing was hit
	if (!hitComponent)
	{
		return;
	}

	// Return if there is no actor
	hitActor = hitComponent->GetOwner();
	if (!hitActor)
	{
		return;
	}

	// Return if the hit actor is not a card, otherwise cast it into an ACardActor
	if ( hitActor->IsA(ACardActor::StaticClass()) )
	{
		UE_LOG(LogTemp, Display, TEXT("Hit actor is a Card"));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Hit actor is NOT a Card. Hit actor class name: %s."), *hitActor->GetClass()->GetName()); 
		return;
	}
	card = Cast<ACardActor>(hitActor);

	// Return if we do not have a hit card
	if (!card)
	{
		return;
	}

	// Return if the card hit is the equipped card
	if (card == equippedCard)
	{
		return;
	}

	// If we already have an equipped card, unequip it
	if (equippedCard)
	{
		UnequipCard(equippedCard);
	}

	// Equip the card and append it to the card inventory  
	EquipCard(card);
	cardsInInventory.Push(card);
	++equippedCardPos;

}

// Throw equipped object ( card )
void AMainCharacter::Throw()
{
	// If nothing is equipped, return
	if (!equippedCard)
	{
		return;
	}

	// Return if there is no mesh found for the currently equipped card
	UStaticMeshComponent* mesh;
	mesh = equippedCard->cardMesh;
	if (!mesh)
	{
		UE_LOG(LogTemp, Display, TEXT("No card mesh found"));
		return;
	}

	// Throw the currently equipped card
	equippedCard->SetIsCardEquipped(false);
	equippedCard->UnequipCard();
	mesh->SetSimulatePhysics(true);
	mesh->AddImpulse(
		(
			playerCamera->GetForwardVector() * FVector(throwVelocity, throwVelocity, throwVelocity)
			)
		+ FVector(0, 0, throwHeight)
	);

	// Remove the card from the inventory
	cardsInInventory.RemoveSingle(equippedCard);
	
	if (equippedCardPos == 0)
	{
		equippedCardPos = cardsInInventory.Num() - 1;
	}
	else
	{
		--equippedCardPos;
	}

	equippedCard = nullptr;

	// If there are more cards in the inventory, equip the next one 
	if (equippedCardPos >= 0)
	{
		ACardActor* nextEquippedCard;
		nextEquippedCard = cardsInInventory[equippedCardPos];
		if (nextEquippedCard) EquipCard(nextEquippedCard);
	}

}

// When the player scrolls up, iterate positively through the inventory
void AMainCharacter::ScrollUp()
{
	if (cardsInInventory.IsEmpty())
	{
		return;
	}

	if(!equippedCard)
	{
		return;
	}
	
	int tempPos;

	if (equippedCardPos == (cardsInInventory.Num() - 1))
	{
		tempPos = 0;
		equippedCardPos = 0;
	}
	else
	{
		++equippedCardPos;
		tempPos = equippedCardPos;
	}
	
	UnequipCard(equippedCard);
	equippedCard->UnequipCard();
	EquipCard(cardsInInventory[tempPos]);
}

// When the player scrolls up, iterate negatively through the inventory
void AMainCharacter::ScrollDown()
{
	if (cardsInInventory.IsEmpty())
	{
		return;
	}

	if (!equippedCard)
	{
		return;
	}

	int tempPos;

	if (equippedCardPos == 0)
	{
		tempPos = cardsInInventory.Num() - 1;
		equippedCardPos = cardsInInventory.Num() - 1;
	}
	else
	{
		--equippedCardPos;
		tempPos = equippedCardPos;
	}

	UnequipCard(equippedCard);
	equippedCard->UnequipCard();
	EquipCard(cardsInInventory[tempPos]);
	
}

// Hide/unhide inventory on press of Tab key
void AMainCharacter::ToggleInventory()
{
	if (equippedCard)
	{
		UnequipCard(equippedCard);
		equippedCard = nullptr;
	}
	else
	{
		EquipCard(cardsInInventory[equippedCardPos]);
	}
}

// Handle the card equipping logic and maintain relevant variables, current equipped card, and equipped card position
void AMainCharacter::EquipCard(ACardActor* cardActor)
{
	cardActor->EquipCard(this);
	equippedCard = cardActor;
}

// Handle the card unequipping logic and maintain relevant variables, current equipped card, and equipped card position
void AMainCharacter::UnequipCard(ACardActor* cardActor)
{
	equippedCard->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	equippedCard->SetActorRelativeLocation(FVector(-1000, -1000, -5000));
	equippedCard->SetActorRelativeRotation(FRotator::ZeroRotator);
	equippedCard->SetIsCardEquipped(false);
}
