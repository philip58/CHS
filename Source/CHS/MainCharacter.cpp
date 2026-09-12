// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CardActor.h"
#include "PlayerChairSlot.h"
#include "PlayerHUD.h"
#include "Components/Image.h"
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

	// Check if hovering over an actor or not
	if ( IsValid( actorInView = GetLineTraceHitActor() ) )
	{
		// If hovering over something, call the hovering method  
		HandleHovering(actorInView);
	}
	else
	{
		// If nothing is being hovered, clear the interact text
		gameModeBase->playerHUD->SetInteractPopupText("");
	}

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
	// If player is seated, disable movement
	if (bIsPlayerSitting)
	{
		return;
	}

	// Move player
	AddMovementInput(GetActorForwardVector(), input);
}

// Move the player backwards
void AMainCharacter::WalkBackwards(float input)
{
	// If player is seated, disable movement
	if (bIsPlayerSitting)
	{
		return;
	}

	// Move player
	AddMovementInput(GetActorForwardVector(), -input);
}

// Move the player left
void AMainCharacter::WalkLeft(float input)
{
	// If player is seated, disable movement
	if (bIsPlayerSitting)
	{
		return;
	}

	// Move player
	AddMovementInput(GetActorRightVector(), -input);
}

// Move the player right
void AMainCharacter::WalkRight(float input)
{
	// If player is seated, disable movement
	if (bIsPlayerSitting)
	{
		return;
	}

	// Move player
	AddMovementInput(GetActorRightVector(), input);
}

// Player jump
void AMainCharacter::PlayerJump()
{
	// If seated, leave chair instead of jumping
	if (bIsPlayerSitting)
	{
		LeaveChair();
		return;
	}

	// If not seated, jump
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

	AActor* hitActor;
	if ( !IsValid( hitActor = GetLineTraceHitActor() ) )
	{
		return;
	}

	// If the hit actor is a card, call card interaction method
	if (hitActor->IsA(ACardActor::StaticClass()) )
	{
		InteractWithCard(hitActor);
	}
	
	// If the hit actor is a chair, call the chair interaction method
	if (hitActor->IsA(APlayerChairSlot::StaticClass()))
	{
		InteractWithChair(hitActor);
	}
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
	UBoxComponent* boxComp;
	boxComp = equippedCard->cardBoxCollision;
	if (!boxComp)
	{
		UE_LOG(LogTemp, Display, TEXT("No card collision found"));
		return;
	}

	// Throw the currently equipped card
	equippedCard->SetIsCardEquipped(false);
	equippedCard->UnequipCard();
	boxComp->SetSimulatePhysics(true);
	boxComp->AddImpulse(
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
		return;
	}
	
	// If inventory is empty, remove card image from inventory ui
	if (gameModeBase && gameModeBase->playerHUD)
	{
		gameModeBase->playerHUD->SetInventoryImage(playerHUD->inventoryImage1, cardInventoryImg, 0);
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
	// Deal with toggling inventory on/off
	if (equippedCard)
	{
		// If card is equipped, toggle off inventory and unequip card
		UnequipCard(equippedCard);
		equippedCard = nullptr;
		bIsInventoryTogggled = false;
		return;
	}
	else if (cardsInInventory.Num() != 0)
	{
		// If card is not equipped, and invetory is not empty toggle on inventory and equip last picked up card
		EquipCard(cardsInInventory[equippedCardPos]);
		bIsInventoryTogggled = true;
		return;
	}

	// If none of the above apply (inventory is empty), negate inventory toggled boolean
	bIsInventoryTogggled = !bIsInventoryTogggled;
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

// Interact with the hit card actor
void AMainCharacter::InteractWithCard(AActor* interactedActor)
{
	// Get card from actor
	ACardActor* card;
	card = Cast<ACardActor>(interactedActor);

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

	// If inventory is empty, change inventory image to card img
	if (cardsInInventory.Num() == 0)
	{
		if (gameModeBase && gameModeBase->playerHUD)
		{
			gameModeBase->playerHUD->SetInventoryImage(playerHUD->inventoryImage1, cardInventoryImg, 1.0f);
		}

	}

	// Equip the card and append it to the card inventory if inventory is on, otherwise just append
	EquipCard(card);
	if (!bIsInventoryTogggled)
	{
		UnequipCard(equippedCard);
		equippedCard = nullptr;
	}
	cardsInInventory.Push(card);
	++equippedCardPos;
}

// Interact with hit chair actor 
void AMainCharacter::InteractWithChair(AActor* interactedActor)
{
	// Get chair from actor
	APlayerChairSlot* chair;
	chair = Cast<APlayerChairSlot>(interactedActor);

	// Set currently sat in chair
	if (chair)
	{
		playerChair = chair;
	}

	// Set the player sitting in chair variables and disable movement
	if (!playerChair->GetIsSatIn())
	{
		playerChair->SetIsSatIn(true);
		bIsPlayerSitting = true;
		if (gameModeBase && gameModeBase->playerMovementComponent)
		{
			gameModeBase->playerMovementComponent->SetMovementMode(EMovementMode::MOVE_None);
			this->SetActorLocation(playerChair->GetActorLocation() - FVector(0,0,chairSitOffset));
		}
	}
}

// Player leave chair
void AMainCharacter::LeaveChair()
{
	// Return if not playerchair found
	if (!playerChair)
	{
		return;
	}

	// Move player away from chair and unset player sitting variables
	this->SetActorLocation(this->GetActorLocation() + FVector(0, 0, distanceFromChair) );
	
	bIsPlayerSitting = false;
	playerChair->SetIsSatIn(false);
	playerChair = nullptr;

	// Re-enable character movement
	if (gameModeBase && gameModeBase->playerMovementComponent)
	{
		gameModeBase->playerMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
		gameModeBase->playerMovementComponent->AddImpulse(FVector(0, 0, chairExitVelocity));
	}

}

// Line trace every frame and handle interactable items
AActor* AMainCharacter::GetLineTraceHitActor()
{
	// Initialize helper variables for line tracing and collision handling 
	FHitResult hitResult;
	FVector forwardVector = playerCamera->GetForwardVector();
	FVector cameraLocation = playerCamera->GetComponentLocation();

	// Draw the line trace and check what was hit
	/*DrawDebugLine
	(
		gameModeBase->playerWorld,
		cameraLocation + (forwardVector * FVector(lineTraceStartOffset, lineTraceStartOffset, lineTraceStartOffset)),
		cameraLocation + forwardVector * FVector(lineTraceLength, lineTraceLength, lineTraceLength),
		FColor::Cyan, true, 5.0);*/

	// Line trace to see if the player is looking directly at something that they can interact with
	gameModeBase->playerWorld->LineTraceSingleByChannel
	(
		hitResult,
		cameraLocation + (forwardVector * FVector(lineTraceStartOffset, lineTraceStartOffset, lineTraceStartOffset)),
		cameraLocation + (forwardVector * FVector(lineTraceLength, lineTraceLength, lineTraceLength)),
		ECollisionChannel::ECC_Visibility
	);

	// Helper variables
	UPrimitiveComponent* hitComponent;
	AActor* hitActor;
	hitComponent = hitResult.GetComponent();

	// Return if nothing was hit
	if (!hitComponent)
	{
		return nullptr;
	}

	// Return if there is no actor
	hitActor = hitComponent->GetOwner();
	if (!hitActor)
	{
		return nullptr;
	}

	return hitActor;
}

// Handle logic when hovering over an actor with line trace
void AMainCharacter::HandleHovering(AActor* hoveredActor)
{
	// Return if no gamemode base and no HUD
	if (!gameModeBase || !gameModeBase->playerHUD)
	{
		return;
	}

	// If the actor is a card, call card hover method
	if (hoveredActor->IsA(ACardActor::StaticClass()))
	{
		CardHover(hoveredActor);
		gameModeBase->playerHUD->SetInteractPopupText("Press E to Interact");
		return;
	}

	// If the hit actor is a chair, call the chair hover method
	if (hoveredActor->IsA(APlayerChairSlot::StaticClass()))
	{
		ChairHover(hoveredActor);
		gameModeBase->playerHUD->SetInteractPopupText("Press E to Interact");
		return;
	}

	// If nothing is being hovered, clear the interact text
	gameModeBase->playerHUD->SetInteractPopupText("");
}

// Handle loggic while hovering over a chair
void AMainCharacter::CardHover(AActor* hoveredActor)
{
	// Get chair from actor
	ACardActor* card;
	card = Cast<ACardActor>(hoveredActor);
	UE_LOG(LogTemp, Display, TEXT("Hovered over card"));
}

// Handle loggic while hovering over a chair
void AMainCharacter::ChairHover(AActor* hoveredActor)
{
	// Get chair from actor
	APlayerChairSlot* chair;
	chair = Cast<APlayerChairSlot>(hoveredActor);
	UE_LOG(LogTemp, Display, TEXT("Hovered over chair"));
}