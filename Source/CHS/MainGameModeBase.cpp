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

    PopulateDecks();

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
	SpawnAndAddCard(cardAceHeartsMesh);
	SpawnAndAddCard(cardTwoHeartsMesh);
	SpawnAndAddCard(cardThreeHeartsMesh);
	SpawnAndAddCard(cardFourHeartsMesh);
	SpawnAndAddCard(cardFiveHeartsMesh);
	SpawnAndAddCard(cardSixHeartsMesh);
	SpawnAndAddCard(cardSevenHeartsMesh);
	SpawnAndAddCard(cardEightHeartsMesh);
	SpawnAndAddCard(cardNineHeartsMesh);
	SpawnAndAddCard(cardTenHeartsMesh);
	SpawnAndAddCard(cardJackHeartsMesh);
	SpawnAndAddCard(cardQueenHeartsMesh);
	SpawnAndAddCard(cardKingHeartsMesh);

	// Spawn diamonds
	SpawnAndAddCard(cardAceDiamondsMesh);
	SpawnAndAddCard(cardTwoDiamondsMesh);
	SpawnAndAddCard(cardThreeDiamondsMesh);
	SpawnAndAddCard(cardFourDiamondsMesh);
	SpawnAndAddCard(cardFiveDiamondsMesh);
	SpawnAndAddCard(cardSixDiamondsMesh);
	SpawnAndAddCard(cardSevenDiamondsMesh);
	SpawnAndAddCard(cardEightDiamondsMesh);
	SpawnAndAddCard(cardNineDiamondsMesh);
	SpawnAndAddCard(cardTenDiamondsMesh);
	SpawnAndAddCard(cardJackDiamondsMesh);
	SpawnAndAddCard(cardQueenDiamondsMesh);
	SpawnAndAddCard(cardKingDiamondsMesh);

	// Spawn clubs
	SpawnAndAddCard(cardAceClubsMesh);
	SpawnAndAddCard(cardTwoClubsMesh);
	SpawnAndAddCard(cardThreeClubsMesh);
	SpawnAndAddCard(cardFourClubsMesh);
	SpawnAndAddCard(cardFiveClubsMesh);
	SpawnAndAddCard(cardSixClubsMesh);
	SpawnAndAddCard(cardSevenClubsMesh);
	SpawnAndAddCard(cardEightClubsMesh);
	SpawnAndAddCard(cardNineClubsMesh);
	SpawnAndAddCard(cardTenClubsMesh);
	SpawnAndAddCard(cardJackClubsMesh);
	SpawnAndAddCard(cardQueenClubsMesh);
	SpawnAndAddCard(cardKingClubsMesh);

	// Spawn spades
	SpawnAndAddCard(cardAceSpadesMesh);
	SpawnAndAddCard(cardTwoSpadesMesh);
	SpawnAndAddCard(cardThreeSpadesMesh);
	SpawnAndAddCard(cardFourSpadesMesh);
	SpawnAndAddCard(cardFiveSpadesMesh);
	SpawnAndAddCard(cardSixSpadesMesh);
	SpawnAndAddCard(cardSevenSpadesMesh);
	SpawnAndAddCard(cardEightSpadesMesh);
	SpawnAndAddCard(cardNineSpadesMesh);
	SpawnAndAddCard(cardTenSpadesMesh);
	SpawnAndAddCard(cardJackSpadesMesh);
	SpawnAndAddCard(cardQueenSpadesMesh);
	SpawnAndAddCard(cardKingSpadesMesh);

	// Spawn Jokers
	SpawnAndAddCard(cardRedJokerMesh);
	SpawnAndAddCard(cardBlackJokerMesh);

	// Add a bigger offset to distinguish the two separate decks
	spawnOffsetCounter += 50;

	// Spawn red cards
	SpawnAndAddCard(cardZeroRedMesh);
	SpawnAndAddCard(cardOneRedMesh);
	SpawnAndAddCard(cardTwoRedMesh);
	SpawnAndAddCard(cardThreeRedMesh);
	SpawnAndAddCard(cardFourRedMesh);
	SpawnAndAddCard(cardFiveRedMesh);
	SpawnAndAddCard(cardSixRedMesh);
	SpawnAndAddCard(cardSevenRedMesh);
	SpawnAndAddCard(cardEightRedMesh);
	SpawnAndAddCard(cardNineRedMesh);
	SpawnAndAddCard(cardSkipRedMesh);
	SpawnAndAddCard(cardReverseRedMesh);
	SpawnAndAddCard(cardDrawTwoRedMesh);

	// Spawn blue cards
	SpawnAndAddCard(cardZeroBlueMesh);
	SpawnAndAddCard(cardOneBlueMesh);
	SpawnAndAddCard(cardTwoBlueMesh);
	SpawnAndAddCard(cardThreeBlueMesh);
	SpawnAndAddCard(cardFourBlueMesh);
	SpawnAndAddCard(cardFiveBlueMesh);
	SpawnAndAddCard(cardSixBlueMesh);
	SpawnAndAddCard(cardSevenBlueMesh);
	SpawnAndAddCard(cardEightBlueMesh);
	SpawnAndAddCard(cardNineBlueMesh);
	SpawnAndAddCard(cardSkipBlueMesh);
	SpawnAndAddCard(cardReverseBlueMesh);
	SpawnAndAddCard(cardDrawTwoBlueMesh);

	// Spawn green cards
	SpawnAndAddCard(cardZeroGreenMesh);
	SpawnAndAddCard(cardOneGreenMesh);
	SpawnAndAddCard(cardTwoGreenMesh);
	SpawnAndAddCard(cardThreeGreenMesh);
	SpawnAndAddCard(cardFourGreenMesh);
	SpawnAndAddCard(cardFiveGreenMesh);
	SpawnAndAddCard(cardSixGreenMesh);
	SpawnAndAddCard(cardSevenGreenMesh);
	SpawnAndAddCard(cardEightGreenMesh);
	SpawnAndAddCard(cardNineGreenMesh);
	SpawnAndAddCard(cardSkipGreenMesh);
	SpawnAndAddCard(cardReverseGreenMesh);
	SpawnAndAddCard(cardDrawTwoGreenMesh);

	// Spawn yellw cards
	SpawnAndAddCard(cardZeroYellowMesh);
	SpawnAndAddCard(cardOneYellowMesh);
	SpawnAndAddCard(cardTwoYellowMesh);
	SpawnAndAddCard(cardThreeYellowMesh);
	SpawnAndAddCard(cardFourYellowMesh);
	SpawnAndAddCard(cardFiveYellowMesh);
	SpawnAndAddCard(cardSixYellowMesh);
	SpawnAndAddCard(cardSevenYellowMesh);
	SpawnAndAddCard(cardEightYellowMesh);
	SpawnAndAddCard(cardNineYellowMesh);
	SpawnAndAddCard(cardSkipYellowMesh);
	SpawnAndAddCard(cardReverseYellowMesh);
	SpawnAndAddCard(cardDrawTwoYellowMesh);

	// Spawn wild cards
	SpawnAndAddCard(cardWildMesh);
	SpawnAndAddCard(cardWildDrawFourMesh);
}

void AMainGameModeBase::SpawnAndAddCard(UStaticMesh* cardMesh)
{
    // If no player world or card mesh return
    if (!playerWorld || !cardMesh || !mainCharacter)
    {
        return;
    }

	// Spawn the card
	spawnOffsetCounter += 20;
    FActorSpawnParameters spawnParams;
    ACardActor* newCard;
	FTransform transform = FTransform::Identity;
	transform.SetLocation(mainCharacter->GetActorLocation() + FVector( spawnOffsetCounter - 600, -400, 0));
    spawnParams.Owner = this;
	
	newCard = playerWorld->SpawnActor<ACardActor>(cardActorClass, transform, spawnParams);

	if (!newCard)
	{
		return;
	}

	// Set card new mesh and push to deck array, then set physics simulate false
	newCard->SetCardMesh(cardMesh);
	cardDeck.Push(newCard);
	newCard->cardMesh->SetSimulatePhysics(false);
	newCard->cardBoxCollision->SetSimulatePhysics(false);

}

void AMainGameModeBase::SpawnCardActor()
{

}