// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CardActor.h"
#include "PlayerChairSlot.h"
#include "PlayerHUD.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "CardTableSlot.h"
#include "GameStartButton.h"
#include "CardGameTable.h"
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

	// Set playerMesh
	playerMesh = this->GetMesh();

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
	
		// Set up player HUD
		playerController = Cast<APlayerController>(GetController());

		if (playerController && playerController->IsLocalController())
		{
			playerHUD = CreateWidget<UPlayerHUD>(playerController, gameModeBase->playerHUDClass);
		}		

		if (playerHUD)
		{
			playerHUD->AddToViewport();

			// Add inventory widgets to arrays
			PopulateInventoryImageSlotArray(playerHUD);
		}

		// Populate the card decks
		gameModeBase->PopulateDecks();
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
	if ( !bIsInventoryExpanded && IsValid( actorInView = GetLineTraceHitActor() ) )
	{
		// If hovering over something, call the hovering method  
		HandleHovering(actorInView);
	}
	else
	{
		// If nothing is being hovered, clear the interact text
		if(playerHUD)
		{
			playerHUD->SetInteractPopupText("");
		}
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

	// Bind action mappings (jump, sprint, interact, throw, scroll up/down, toggle inventory, navigate through inventory slots 1-6)
	playerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainCharacter::PlayerJump);
	playerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &AMainCharacter::StartSprinting);
	playerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &AMainCharacter::StopSprinting);
	playerInputComponent->BindAction("Interact", EInputEvent::IE_Released, this, &AMainCharacter::Interact);
	playerInputComponent->BindAction("Throw", EInputEvent::IE_Released, this, &AMainCharacter::Throw);
	playerInputComponent->BindAction("ScrollUp", EInputEvent::IE_Pressed, this, &AMainCharacter::ScrollUp);
	playerInputComponent->BindAction("ScrollDown", EInputEvent::IE_Pressed, this, &AMainCharacter::ScrollDown);
	playerInputComponent->BindAction("SelectInventorySlot1", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot1);
	playerInputComponent->BindAction("SelectInventorySlot2", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot2);
	playerInputComponent->BindAction("SelectInventorySlot3", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot3);
	playerInputComponent->BindAction("SelectInventorySlot4", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot4);
	playerInputComponent->BindAction("SelectInventorySlot5", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot5);
	playerInputComponent->BindAction("SelectInventorySlot6", EInputEvent::IE_Pressed, this, &AMainCharacter::SelectInventorySlot6);
	playerInputComponent->BindAction("ToggleCardInventory", EInputEvent::IE_Pressed, this, &AMainCharacter::ToggleCardInventory); 
}

// Move the player forward
void AMainCharacter::WalkForward(float input)
{
	// If player is seated, disable movement
	if (bStopCharacterMovement)
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
	if (bStopCharacterMovement)
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
	if (bStopCharacterMovement)
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
	if (bStopCharacterMovement)
	{
		return;
	}

	// Move player
	AddMovementInput(GetActorRightVector(), input);
}

// Player jump
void AMainCharacter::PlayerJump()
{
	// No jumping when inventory is open
	if (bIsInventoryExpanded) return;

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
	// Return if card inventory expanded
	if (bIsInventoryExpanded) return;

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
	// If card is equipped and the hit actor is a table card slot, place the card
	else if (equippedCard != nullptr && hitActor->IsA(ACardTableSlot::StaticClass()))
	{
		//ACardActor* tempCard = equippedCard;
		//UnequipAndRemoveCard();
		//tempCard->SetIsCardEquipped(false);
		//tempCard->UnequipCard();
		//tempCard->PlaceCardInTableSlot(hitActor);
	}
	
	// If the hit actor is a chair, call the chair interaction method
	if (hitActor->IsA(APlayerChairSlot::StaticClass()))
	{
		InteractWithChair(hitActor);
	}

	if (hitActor->IsA(AGameStartButton::StaticClass()))
	{
		InteractWithGameStartButton(hitActor);
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

	UnequipAndRemoveCard();

}

// When the player scrolls up, iterate positively through the inventory
void AMainCharacter::ScrollUp()
{
	if (bIsInventoryExpanded) return;
	IncrementThroughInventory(1);
	//IncrementThroughCards(1);
}

// When the player scrolls up, iterate negatively through the inventory
void AMainCharacter::ScrollDown()
{
	if (bIsInventoryExpanded) return;
	IncrementThroughInventory(-1);
	//IncrementThroughCards(-1);
}

// Hide/unhide card from hand, if bool is true then we hide otherwise equip
void AMainCharacter::ToggleCardHide(bool bHide)
{
	// Deal with toggling card hide on/off
	if (bHide && equippedCard)
	{
		// If card is equipped, toggle off card hide 
		UnequipCard(equippedCard);
		equippedCard = nullptr;
		bIsCardVisible = false;
		return;
	}
	else if(!bHide && cardsInInventory.Num() > 0)
	{
		// If card is not equipped, and inventory is not empty toggle on inventory and equip last picked up card
		EquipCard(cardsInInventory[equippedCardPos]);
		bIsCardVisible = true;
		return;
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
	AActor* attachedActor = cardActor->GetAttachParentActor();
	if(attachedActor) cardActor->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
	cardActor->SetActorRelativeLocation(FVector(-1000, -1000, -5000));
	cardActor->SetActorRelativeRotation(FRotator::ZeroRotator);
	cardActor->SetIsCardEquipped(false);
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
		if (gameModeBase && playerHUD && inventoryImageArray[inventoryPos] && inventorySlotArray[inventoryPos])
		{
			playerHUD->SetInventoryImage(inventoryImageArray[inventoryPos], cardInventoryImg, 1.0f);
			playerHUD->SetInventorySlotColor
			(
				inventorySlotArray[inventoryPos],
				rSelectedColorInventorySlot,
				gSelectedColorInventorySlot,
				bSelectedColorInventorySlot,
				aSelectedColorInventorySlot
			);
		}

	}

	// Equip the card and append it to the card inventory if inventory is on, otherwise just append
	EquipCard(card);
	if (!bIsCardVisible)
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
		playerChair->SetCharacterInChair(this);
		bStopCharacterMovement = true;
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
	
	// Set player left chair variables
	bStopCharacterMovement = false;
	bIsPlayerSitting = false;
	playerChair->SetIsSatIn(false);
	AActor* chairOwner = playerChair->GetOwner();
	ACardGameTable* chairOwningTable = Cast<ACardGameTable>(chairOwner);
	if (chairOwningTable && !chairOwningTable->bIsGameRunning)
	{
		playerChair->SetCharacterInChair(nullptr);
		playerChair = nullptr;
	}
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
	if (!gameModeBase || !playerHUD)
	{
		return;
	}

	// If the actor is a card, call card hover method
	if (hoveredActor->IsA(ACardActor::StaticClass()))
	{
		playerHUD->SetInteractPopupText("Press E To Pick Up");
		return;
	}

	// If the hit actor is a chair, call the chair hover method
	if (hoveredActor->IsA(APlayerChairSlot::StaticClass()))
	{
		playerHUD->SetInteractPopupText("Press E To Sit");
		return;
	}

	// If player is holding a card and the hit actor is a card slot
	if (equippedCard && hoveredActor->IsA(ACardTableSlot::StaticClass()) )
	{
		//playerHUD->SetInteractPopupText("Press E To Place");
		//return; 
	}

	// If player is hovering over the game start button change the pop up text
	if (hoveredActor->IsA(AGameStartButton::StaticClass()))
	{
		AGameStartButton* button;
		button = Cast<AGameStartButton>(hoveredActor);
		bool hasGameStarted = false;
		if (button) hasGameStarted = button->GetGameHasStarted();
		if (!hasGameStarted)
		{
			playerHUD->SetInteractPopupText("Press E To Start Game");
		}
		else
		{
			playerHUD->SetInteractPopupText("");
		}
		return;
	}

	// If nothing is being hovered, clear the interact text
	playerHUD->SetInteractPopupText("");
}

// Increment through the cards up or down depending on int (-1 or 1)
void AMainCharacter::IncrementThroughCards(const int& increment)
{
	// Return if no cards in inventory
	if (cardsInInventory.IsEmpty())
	{
		return;
	}

	// Return if there is no equipped card
	if (!equippedCard)
	{
		return;
	}

	// Depending on if decrementing or incrementing, determine next card inventory position
	int tempPos = 0;
	if (increment > 0)
	{
		// Increment
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
	}
	else if (increment < 0)
	{
		// Decrement
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
	}

	// Equip next card
	UnequipCard(equippedCard);
	equippedCard->UnequipCard();
	EquipCard(cardsInInventory[tempPos]);
}

// Increment through the inventory up or down depending on int (-1 or 1)
void AMainCharacter::IncrementThroughInventory(const int& increment)
{
	// Return if HUD does not exist or if any inventory array is empty
	if (!IsValid(playerHUD) || inventoryImageArray.Num() <= 0 || inventorySlotArray.Num() <= 0 )
	{
		return;
	}

	// Depending on if decrementing or incrementing, determine next inventory position
	int tempPos = 0;
	if (increment > 0)
	{
		// Increment
		if (inventoryPos == (inventorySlotArray.Num() - 1))
		{
			tempPos = 0;
		}
		else
		{
			tempPos = inventoryPos + 1;
		}
	}
	else if (increment < 0)
	{
		// Decrement
		if (inventoryPos == 0)
		{
			tempPos = inventorySlotArray.Num() - 1;
		}
		else
		{
			tempPos = inventoryPos - 1;
		}
	}

	// Highlight next slot and unhighlight previous
	HighlightSelectedInventorySlot(tempPos);

}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot1()
{
	NavigateToSelectedInventorySlot(0);
}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot2()
{
	NavigateToSelectedInventorySlot(1);
}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot3()
{
	NavigateToSelectedInventorySlot(2);
}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot4()
{
	NavigateToSelectedInventorySlot(3);
}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot5()
{
	NavigateToSelectedInventorySlot(4);
}

// Pass the selected inventory slot 
void AMainCharacter::SelectInventorySlot6()
{
	NavigateToSelectedInventorySlot(5);
}

// Navigate to the selected inventory slot
void AMainCharacter::NavigateToSelectedInventorySlot(int inventorySlotNumber)
{
	// Return if HUD does not exist or if any inventory array is empty
	if (!IsValid(playerHUD) || inventoryImageArray.Num() <= 0 || inventorySlotArray.Num() <= 0)
	{
		return;
	}

	// Highlight next slot and unhighlight previous
	HighlightSelectedInventorySlot(inventorySlotNumber);
}

// Highlight inventory slot we navigate to and unhighlight previous
void AMainCharacter::HighlightSelectedInventorySlot(int inventorySlot)
{
	// Set inventory slot/image attributes for old/new positions
	playerHUD->SetInventorySlotColor
	(
		inventorySlotArray[inventoryPos],
		rDefaultColorInventorySlot,
		gDefaultColorInventorySlot,
		bDefaultColorInventorySlot,
		aDefaultColorInventorySlot
	);
	playerHUD->SetInventorySlotColor
	(
		inventorySlotArray[inventorySlot],
		rSelectedColorInventorySlot,
		gSelectedColorInventorySlot,
		bSelectedColorInventorySlot,
		aSelectedColorInventorySlot
	);

	inventoryPos = inventorySlot;

	// Toggle hiding card if we move onto or away from the inventory slot holding the card
	UObject* object = inventoryImageArray[inventoryPos]->GetBrush().GetResourceObject();
	UTexture2D* texture = Cast<UTexture2D>(object);
	if (texture && inventoryImageArray[inventoryPos]->GetBrush().GetResourceObject() == cardInventoryImg)
	{
		ToggleCardHide(false);
	}
	else
	{
		ToggleCardHide(true);
	}
}


// Unequip currently equipped card and remove it from card inventory
void AMainCharacter::UnequipAndRemoveCard()
{
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
	if (gameModeBase && playerHUD && inventoryImageArray[inventoryPos] && inventorySlotArray[inventoryPos])
	{
		playerHUD->SetInventoryImage(inventoryImageArray[inventoryPos], blankInventoryImg, 0.0);
		playerHUD->SetInventorySlotColor
		(
			inventorySlotArray[inventoryPos],
			rDefaultColorInventorySlot,
			gDefaultColorInventorySlot,
			bDefaultColorInventorySlot,
			aDefaultColorInventorySlot
		);
	}
}

// Handle interacting with the game start button
void AMainCharacter::InteractWithGameStartButton(AActor* actor)
{
	// Return if no gamemode base or no deck 
	if (!gameModeBase || gameModeBase->specialDeck.Num() <= 0)
	{
		return;
	}

	// Cast actor to game start button 
	AGameStartButton* interactedGameStartButton;
	interactedGameStartButton = Cast<AGameStartButton>(actor);
	AActor* owningActor = interactedGameStartButton->GetOwner();
	ACardGameTable* owningGameTable;
	if (!owningActor) return;
	owningGameTable = Cast<ACardGameTable>(owningActor);
	if (!owningGameTable) return;

	// Start the game only if its not started
	if (owningGameTable->bIsGameRunning) return;
	if (interactedGameStartButton) owningGameTable->StartMainGameLoop(interactedGameStartButton);
}

// Add inventory widgets to arrays
void AMainCharacter::PopulateInventoryImageSlotArray(TObjectPtr<UPlayerHUD> hud)
{
	inventoryImageArray.Push(hud->inventoryImage1);
	inventoryImageArray.Push(hud->inventoryImage2);
	inventoryImageArray.Push(hud->inventoryImage3);
	inventoryImageArray.Push(hud->inventoryImage4);
	inventoryImageArray.Push(hud->inventoryImage5);
	inventoryImageArray.Push(hud->inventoryImage6);
	inventorySlotArray.Push(hud->inventorySlot1);
	inventorySlotArray.Push(hud->inventorySlot2);
	inventorySlotArray.Push(hud->inventorySlot3);
	inventorySlotArray.Push(hud->inventorySlot4);
	inventorySlotArray.Push(hud->inventorySlot5);
	inventorySlotArray.Push(hud->inventorySlot6);
}

// Toggle the card inventory on press of tab key, expands all cards for player
void AMainCharacter::ToggleCardInventory()
{
	if (bIsInventoryExpanded)
	{
		bIsInventoryExpanded = false;
	} 
	else
	{
		bIsInventoryExpanded = true;
	}

	// Return if card inventory empty
	if (cardsInInventory.Num() <= 0)
	{
		return;
	}

	// If bool is true, then we expand the inventory to show all the cards and stop player movement
	if (bIsInventoryExpanded)
	{
		// Helper variables 
		float tempHorizontalOffset = horizontalInventoryOffset;
		float tempForwardOffset = forwardInventoryOffset;
		float tempVerticalOffset = verticalInventoryOffset;
		if (!cardPlaceHolderSocket) return;
		if (!playerCamera) return;
		if (!cardGameTable) return;
		FVector tempCamLocation = playerCamera->GetComponentLocation();
		FVector tempCamForwardVector = playerCamera->GetForwardVector();
		FVector tempCamRightVector = playerCamera->GetRightVector();
		FVector tempCamUpVector = playerCamera->GetUpVector();
		AActor* tempActorCast = Cast<AActor>(this);
		FRotator tempCardRotation = FRotator::ZeroRotator;
		FRotator newCardRotation = FRotator::ZeroRotator;

		bStopCharacterMovement = true;
		ToggleCardHide(true);

		// Alternate between setting location left/right of origin
		for (int i = 0; i < cardsInInventory.Num(); ++i)
		{
			if (!cardsInInventory[i]) continue;
			cardsInInventory[i]->PlaceCardInTableSlot(tempActorCast);
			if (i == 0 || i % cardGameTable->maxCardsPerInventoryRow == 0)
			{
				tempHorizontalOffset = horizontalInventoryOffset;
				if (i % cardGameTable->maxCardsPerInventoryRow == 0)
				{
					tempVerticalOffset += cardInventoryRowDistance;
				}

				cardsInInventory[i]->SetActorLocation(
					tempCamLocation +
					(tempCamForwardVector * inventoryDistanceFromPlayer) +
					(tempCamUpVector * tempVerticalOffset));
				if (i == 0)
				{
					tempCardRotation = cardsInInventory[i]->GetActorRotation();
					newCardRotation = UKismetMathLibrary::FindLookAtRotation(cardsInInventory[i]->GetActorLocation(), tempCamLocation);
				}
			}
			else if (i % 2 == 0)
			{
				cardsInInventory[i]->SetActorLocation(
					tempCamLocation +
					(tempCamForwardVector * inventoryDistanceFromPlayer) +
					(tempCamForwardVector * tempForwardOffset) +
					(tempCamRightVector * (tempHorizontalOffset - horizontalInventoryOffset)) +
					(tempCamUpVector * tempVerticalOffset));
			}
			else
			{
				cardsInInventory[i]->SetActorLocation(
					tempCamLocation +
					(tempCamForwardVector * inventoryDistanceFromPlayer) -
					(tempCamForwardVector * tempForwardOffset) -
					(tempCamRightVector * tempHorizontalOffset) +
					(tempCamUpVector * tempVerticalOffset));
			}

			cardsInInventory[i]->SetActorRotation(FRotator(newCardRotation.Pitch + 180, tempCardRotation.Yaw, tempCardRotation.Roll));
			tempHorizontalOffset += horizontalInventoryOffset;
			tempForwardOffset += forwardInventoryOffset;
		}
	}
	// If bool is false, put all the cards away and equip the current card in inventory and resume character movement
	else
	{
		bStopCharacterMovement = false;
		for (int i = 0; i < cardsInInventory.Num(); ++i)
		{
			UnequipCard(cardsInInventory[i]);
		}

		EquipCard(cardsInInventory[equippedCardPos]);
	}
}

// Set the card game table the player is palying at
void AMainCharacter::SetCardGameTable(ACardGameTable* newCardGameTable)
{
	if(newCardGameTable) cardGameTable = newCardGameTable;
}
