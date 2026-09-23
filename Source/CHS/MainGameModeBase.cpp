// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "PlayerHUD.h"
#include "CardActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Class constructor
AMainGameModeBase::AMainGameModeBase()
{
	
}

// Begin play, called once at the start of the game
void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	playerWorld = this->GetWorld(); 
	
	// Get the world
	if (playerWorld)
	{
		playerController = playerWorld->GetFirstPlayerController();
	}

	// Get main character  
	if (playerController)
	{
		// Try to cast player character to AMainCharacter class
		try
		{
			mainCharacter = playerController->GetCharacter();
		}
		catch (const std::exception&)
		{
			UE_LOG(LogTemp, Display, TEXT("Exception caught: issue with casting character to main character!"));
		}
	}
	
	// Get player movement component
	if (mainCharacter)
	{
		playerMovementComponent = mainCharacter->GetCharacterMovement();
	}

	// Set up player HUD
	playerHUD = CreateWidget<UPlayerHUD>(playerController, playerHUDClass);
	if (playerHUD)
	{
		playerHUD->AddToViewport();
	    
		// Add inventory widgets to arrays
		PopulateInventoryImageSlotArray();
	}

	// Populate the card decks
    PopulateDecks();

	// Get the timer manager
	timerManager = playerWorld->GetTimerManager();

}

// Add inventory widgets to arrays
void AMainGameModeBase::PopulateInventoryImageSlotArray()
{
	inventoryImageArray.Push(playerHUD->inventoryImage1);
	inventoryImageArray.Push(playerHUD->inventoryImage2);
	inventoryImageArray.Push(playerHUD->inventoryImage3);
	inventoryImageArray.Push(playerHUD->inventoryImage4);
	inventoryImageArray.Push(playerHUD->inventoryImage5);
	inventoryImageArray.Push(playerHUD->inventoryImage6);
	inventorySlotArray.Push(playerHUD->inventorySlot1);
	inventorySlotArray.Push(playerHUD->inventorySlot2);
	inventorySlotArray.Push(playerHUD->inventorySlot3);
	inventorySlotArray.Push(playerHUD->inventorySlot4);
	inventorySlotArray.Push(playerHUD->inventorySlot5);
	inventorySlotArray.Push(playerHUD->inventorySlot6);
}

// Add cards to deck array
void AMainGameModeBase::PopulateDecks()
{
    // Clear array
    cardDeck.Empty();

	// Spawn hearts
	SpawnAndAddCard(cardAceHeartsMesh, cardDeck);
	SpawnAndAddCard(cardTwoHeartsMesh, cardDeck);
	SpawnAndAddCard(cardThreeHeartsMesh, cardDeck);
	SpawnAndAddCard(cardFourHeartsMesh, cardDeck);
	SpawnAndAddCard(cardFiveHeartsMesh, cardDeck);
	SpawnAndAddCard(cardSixHeartsMesh, cardDeck);
	SpawnAndAddCard(cardSevenHeartsMesh, cardDeck);
	SpawnAndAddCard(cardEightHeartsMesh, cardDeck);
	SpawnAndAddCard(cardNineHeartsMesh, cardDeck);
	SpawnAndAddCard(cardTenHeartsMesh, cardDeck);
	SpawnAndAddCard(cardJackHeartsMesh, cardDeck);
	SpawnAndAddCard(cardQueenHeartsMesh, cardDeck);
	SpawnAndAddCard(cardKingHeartsMesh, cardDeck);

	// Spawn diamonds
	SpawnAndAddCard(cardAceDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardTwoDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardThreeDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardFourDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardFiveDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardSixDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardSevenDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardEightDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardNineDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardTenDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardJackDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardQueenDiamondsMesh, cardDeck);
	SpawnAndAddCard(cardKingDiamondsMesh, cardDeck);

	// Spawn clubs
	SpawnAndAddCard(cardAceClubsMesh, cardDeck);
	SpawnAndAddCard(cardTwoClubsMesh, cardDeck);
	SpawnAndAddCard(cardThreeClubsMesh, cardDeck);
	SpawnAndAddCard(cardFourClubsMesh, cardDeck);
	SpawnAndAddCard(cardFiveClubsMesh, cardDeck);
	SpawnAndAddCard(cardSixClubsMesh, cardDeck);
	SpawnAndAddCard(cardSevenClubsMesh, cardDeck);
	SpawnAndAddCard(cardEightClubsMesh, cardDeck);
	SpawnAndAddCard(cardNineClubsMesh, cardDeck);
	SpawnAndAddCard(cardTenClubsMesh, cardDeck);
	SpawnAndAddCard(cardJackClubsMesh, cardDeck);
	SpawnAndAddCard(cardQueenClubsMesh, cardDeck);
	SpawnAndAddCard(cardKingClubsMesh, cardDeck);

	// Spawn spades
	SpawnAndAddCard(cardAceSpadesMesh, cardDeck);
	SpawnAndAddCard(cardTwoSpadesMesh, cardDeck);
	SpawnAndAddCard(cardThreeSpadesMesh, cardDeck);
	SpawnAndAddCard(cardFourSpadesMesh, cardDeck);
	SpawnAndAddCard(cardFiveSpadesMesh, cardDeck);
	SpawnAndAddCard(cardSixSpadesMesh, cardDeck);
	SpawnAndAddCard(cardSevenSpadesMesh, cardDeck);
	SpawnAndAddCard(cardEightSpadesMesh, cardDeck);
	SpawnAndAddCard(cardNineSpadesMesh, cardDeck);
	SpawnAndAddCard(cardTenSpadesMesh, cardDeck);
	SpawnAndAddCard(cardJackSpadesMesh, cardDeck);
	SpawnAndAddCard(cardQueenSpadesMesh, cardDeck);
	SpawnAndAddCard(cardKingSpadesMesh, cardDeck);

	// Spawn Jokers
	SpawnAndAddCard(cardRedJokerMesh, cardDeck);
	SpawnAndAddCard(cardBlackJokerMesh, cardDeck);

	// Add a bigger offset to distinguish the two separate decks
	spawnOffsetCounter += 50;

	// Spawn red cards
	SpawnAndAddCard(cardZeroRedMesh, specialDeck);
	SpawnAndAddCard(cardOneRedMesh, specialDeck);
	SpawnAndAddCard(cardTwoRedMesh, specialDeck);
	SpawnAndAddCard(cardThreeRedMesh, specialDeck);
	SpawnAndAddCard(cardFourRedMesh, specialDeck);
	SpawnAndAddCard(cardFiveRedMesh, specialDeck);
	SpawnAndAddCard(cardSixRedMesh, specialDeck);
	SpawnAndAddCard(cardSevenRedMesh, specialDeck);
	SpawnAndAddCard(cardEightRedMesh, specialDeck);
	SpawnAndAddCard(cardNineRedMesh, specialDeck);
	SpawnAndAddCard(cardSkipRedMesh, specialDeck);
	SpawnAndAddCard(cardReverseRedMesh, specialDeck);
	SpawnAndAddCard(cardDrawTwoRedMesh, specialDeck);

	// Spawn blue cards
	SpawnAndAddCard(cardZeroBlueMesh, specialDeck);
	SpawnAndAddCard(cardOneBlueMesh, specialDeck);
	SpawnAndAddCard(cardTwoBlueMesh, specialDeck);
	SpawnAndAddCard(cardThreeBlueMesh, specialDeck);
	SpawnAndAddCard(cardFourBlueMesh, specialDeck);
	SpawnAndAddCard(cardFiveBlueMesh, specialDeck);
	SpawnAndAddCard(cardSixBlueMesh, specialDeck);
	SpawnAndAddCard(cardSevenBlueMesh, specialDeck);
	SpawnAndAddCard(cardEightBlueMesh, specialDeck);
	SpawnAndAddCard(cardNineBlueMesh, specialDeck);
	SpawnAndAddCard(cardSkipBlueMesh, specialDeck);
	SpawnAndAddCard(cardReverseBlueMesh, specialDeck);
	SpawnAndAddCard(cardDrawTwoBlueMesh, specialDeck);

	// Spawn green cards
	SpawnAndAddCard(cardZeroGreenMesh, specialDeck);
	SpawnAndAddCard(cardOneGreenMesh, specialDeck);
	SpawnAndAddCard(cardTwoGreenMesh, specialDeck);
	SpawnAndAddCard(cardThreeGreenMesh, specialDeck);
	SpawnAndAddCard(cardFourGreenMesh, specialDeck);
	SpawnAndAddCard(cardFiveGreenMesh, specialDeck);
	SpawnAndAddCard(cardSixGreenMesh, specialDeck);
	SpawnAndAddCard(cardSevenGreenMesh, specialDeck);
	SpawnAndAddCard(cardEightGreenMesh, specialDeck);
	SpawnAndAddCard(cardNineGreenMesh, specialDeck);
	SpawnAndAddCard(cardSkipGreenMesh, specialDeck);
	SpawnAndAddCard(cardReverseGreenMesh, specialDeck);
	SpawnAndAddCard(cardDrawTwoGreenMesh, specialDeck);

	// Spawn yellw cards
	SpawnAndAddCard(cardZeroYellowMesh, specialDeck);
	SpawnAndAddCard(cardOneYellowMesh, specialDeck);
	SpawnAndAddCard(cardTwoYellowMesh, specialDeck);
	SpawnAndAddCard(cardThreeYellowMesh, specialDeck);
	SpawnAndAddCard(cardFourYellowMesh, specialDeck);
	SpawnAndAddCard(cardFiveYellowMesh, specialDeck);
	SpawnAndAddCard(cardSixYellowMesh, specialDeck);
	SpawnAndAddCard(cardSevenYellowMesh, specialDeck);
	SpawnAndAddCard(cardEightYellowMesh, specialDeck);
	SpawnAndAddCard(cardNineYellowMesh, specialDeck);
	SpawnAndAddCard(cardSkipYellowMesh, specialDeck);
	SpawnAndAddCard(cardReverseYellowMesh, specialDeck);
	SpawnAndAddCard(cardDrawTwoYellowMesh, specialDeck);

	// Spawn wild cards
	SpawnAndAddCard(cardWildMesh, specialDeck);
	SpawnAndAddCard(cardWildDrawFourMesh, specialDeck);
}

// Spawn a card actor and add it to the selected deck
void AMainGameModeBase::SpawnAndAddCard(UStaticMesh* cardMesh, TArray<TObjectPtr<ACardActor>>& deck)
{
	// If spawning failed, return
	spawnOffsetCounter += 20;
	FVector spawnLocation = mainCharacter->GetActorLocation() + FVector(spawnOffsetCounter - 600, -400, 0);
	ACardActor* newCard = SpawnCardActor(cardMesh, spawnLocation);
	if (!newCard)
	{
		return;
	}

	// Push the new card to deck array, then set physics simulate false
	deck.Push(newCard);
	newCard->cardMesh->SetSimulatePhysics(false);
	newCard->cardBoxCollision->SetSimulatePhysics(false);

}

// Spawn a card actor at a given location and return the card
ACardActor* AMainGameModeBase::SpawnCardActor(UStaticMesh* cardMesh, const FVector& location)
{
	// If no player world or card mesh return
	if (!playerWorld || !cardMesh || !mainCharacter)
	{
		return nullptr;
	}

	// Spawn the card
	FActorSpawnParameters spawnParams;
	ACardActor* newCard;
	FTransform transform = FTransform::Identity;
	transform.SetLocation(location);
	spawnParams.Owner = this;

	newCard = playerWorld->SpawnActor<ACardActor>(cardActorClass, transform, spawnParams);

	if (!newCard)
	{
		return nullptr;
	}

	newCard->SetCardMesh(cardMesh);
	return newCard;
}