// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "PlayerHUD.h"
#include "CardActor.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"
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
		character = playerController->GetCharacter();
	}
	
	// Get player movement component
	if (character)
	{
		playerMovementComponent = character->GetCharacterMovement();

		mainCharacter = Cast<AMainCharacter>(character);
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
	FVector spawnLocation = character->GetActorLocation() + FVector(spawnOffsetCounter - 600, -400, 0);
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
	if (!playerWorld || !cardMesh || !character)
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

// Main card game loop logic
void AMainGameModeBase::MainGameLoop()
{
	// If no player world or card mesh return
	if (!playerWorld || !mainCharacter || !character)
	{
		UE_LOG(LogTemp, Display, TEXT("Cannot start game because if (!playerWorld || !mainCharacter || !character) returned true"));
		return;
	}

	// Get the number of players playing the game
	UGameplayStatics::GetAllActorsOfClass(playerWorld, mainCharacterClass, mainCharacterActorArray);

	for (AActor* actor : mainCharacterActorArray)
	{
		AMainCharacter* mc = Cast<AMainCharacter>(actor);
		if (mc) mainCharacterArray.Push(mc);
	}

	if (mainCharacterArray.Num() <= 0) return;

	UStaticMesh* mesh;
	ACardActor* card;
	AMainCharacter* tempMainCharacter;

	bIsGameRunning = true;
	while (bIsGameRunning)
	{
		// Spawn a card for each player
		for (int i = 0; i < mainCharacterArray.Num(); ++i)
		{
			mesh = GetRandomCardMesh(specialDeck);
			if (!mesh) continue;
			card = SpawnCardActor(mesh, FVector(0,0,0));
			tempMainCharacter = mainCharacterArray[i];
			tempMainCharacter->InteractWithCard(card);
		}
		bIsGameRunning = false;
	}

}

// Get random card mesh from card array
UStaticMesh* AMainGameModeBase::GetRandomCardMesh(const TArray<TObjectPtr<ACardActor>>& deckArray)
{
	// Get random number between 0 to deck size 
	float randNum = FMath::RandRange(0, deckArray.Num() - 1);
	FMath::FloorToInt(randNum);

	// Get the mesh and return it or nullptr
	UStaticMesh* mesh; 
	UStaticMeshComponent* meshComponent = deckArray[randNum]->cardMesh;
	if (!meshComponent) return nullptr;
	mesh = meshComponent->GetStaticMesh();
	if (!mesh) return nullptr;
	return mesh;

}
