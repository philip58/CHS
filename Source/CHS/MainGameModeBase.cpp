// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "PlayerHUD.h"
#include "CardActor.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "GameStartButton.h"
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

}

// Add cards to deck array
void AMainGameModeBase::PopulateDecks()
{
	// Return if the decks have already been populated
	if (cardDeck.Num() > 0 && specialDeck.Num() > 0)
	{
		return;
	}

	// Spawn hearts
	SpawnAndAddCard(cardAceHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_Ace);
	SpawnAndAddCard(cardTwoHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_3);
	SpawnAndAddCard(cardFourHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_5);
	SpawnAndAddCard(cardSixHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_7);
	SpawnAndAddCard(cardEightHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_8);
	SpawnAndAddCard(cardNineHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_9);
	SpawnAndAddCard(cardTenHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_10);
	SpawnAndAddCard(cardJackHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_Jack);
	SpawnAndAddCard(cardQueenHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_Queen);
	SpawnAndAddCard(cardKingHeartsMesh, cardDeck, ECardType::CT_Heart, ECardValue::CV_King);

	// Spawn diamonds
	SpawnAndAddCard(cardAceDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_Ace);
	SpawnAndAddCard(cardTwoDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_3);
	SpawnAndAddCard(cardFourDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_5);
	SpawnAndAddCard(cardSixDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_7);
	SpawnAndAddCard(cardEightDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_8);
	SpawnAndAddCard(cardNineDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_9);
	SpawnAndAddCard(cardTenDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_10);
	SpawnAndAddCard(cardJackDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_Jack);
	SpawnAndAddCard(cardQueenDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_Queen);
	SpawnAndAddCard(cardKingDiamondsMesh, cardDeck, ECardType::CT_Diamond, ECardValue::CV_King);

	// Spawn clubs
	SpawnAndAddCard(cardAceClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_Ace);
	SpawnAndAddCard(cardTwoClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_3);
	SpawnAndAddCard(cardFourClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_5);
	SpawnAndAddCard(cardSixClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_7);
	SpawnAndAddCard(cardEightClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_8);
	SpawnAndAddCard(cardNineClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_9);
	SpawnAndAddCard(cardTenClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_10);
	SpawnAndAddCard(cardJackClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_Jack);
	SpawnAndAddCard(cardQueenClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_Queen);
	SpawnAndAddCard(cardKingClubsMesh, cardDeck, ECardType::CT_Club, ECardValue::CV_King);

	// Spawn spades
	SpawnAndAddCard(cardAceSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_Ace);
	SpawnAndAddCard(cardTwoSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_3);
	SpawnAndAddCard(cardFourSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_5);
	SpawnAndAddCard(cardSixSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_7);
	SpawnAndAddCard(cardEightSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_8);
	SpawnAndAddCard(cardNineSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_9);
	SpawnAndAddCard(cardTenSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_10);
	SpawnAndAddCard(cardJackSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_Jack);
	SpawnAndAddCard(cardQueenSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_Queen);
	SpawnAndAddCard(cardKingSpadesMesh, cardDeck, ECardType::CT_Spade, ECardValue::CV_King);

	// Spawn Jokers
	SpawnAndAddCard(cardRedJokerMesh, cardDeck, ECardType::CT_Red, ECardValue::CV_Joker);
	SpawnAndAddCard(cardBlackJokerMesh, cardDeck, ECardType::CT_Black, ECardValue::CV_Joker);

	// Add a bigger offset to distinguish the two separate decks
	spawnOffsetCounter += 50;

	// Spawn red cards
	SpawnAndAddCard(cardZeroRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_0);
	SpawnAndAddCard(cardOneRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_1);
	SpawnAndAddCard(cardTwoRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_3);
	SpawnAndAddCard(cardFourRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_5);
	SpawnAndAddCard(cardSixRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_7);
	SpawnAndAddCard(cardEightRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_8);
	SpawnAndAddCard(cardNineRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_9);
	SpawnAndAddCard(cardSkipRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_Skip);
	SpawnAndAddCard(cardReverseRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_Reverse);
	SpawnAndAddCard(cardDrawTwoRedMesh, specialDeck, ECardType::CT_Red, ECardValue::CV_DrawTwo);

	// Spawn blue cards
	SpawnAndAddCard(cardZeroBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_0);
	SpawnAndAddCard(cardOneBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_1);
	SpawnAndAddCard(cardTwoBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_3);
	SpawnAndAddCard(cardFourBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_5);
	SpawnAndAddCard(cardSixBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_7);
	SpawnAndAddCard(cardEightBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_8);
	SpawnAndAddCard(cardNineBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_9);
	SpawnAndAddCard(cardSkipBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_Skip);
	SpawnAndAddCard(cardReverseBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_Reverse);
	SpawnAndAddCard(cardDrawTwoBlueMesh, specialDeck, ECardType::CT_Blue, ECardValue::CV_DrawTwo);

	// Spawn green cards
	SpawnAndAddCard(cardZeroGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_0);
	SpawnAndAddCard(cardOneGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_1);
	SpawnAndAddCard(cardTwoGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_3);
	SpawnAndAddCard(cardFourGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_5);
	SpawnAndAddCard(cardSixGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_7);
	SpawnAndAddCard(cardEightGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_8);
	SpawnAndAddCard(cardNineGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_9);
	SpawnAndAddCard(cardSkipGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_Skip);
	SpawnAndAddCard(cardReverseGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_Reverse);
	SpawnAndAddCard(cardDrawTwoGreenMesh, specialDeck, ECardType::CT_Green, ECardValue::CV_DrawTwo);

	// Spawn yellw cards
	SpawnAndAddCard(cardZeroYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_0);
	SpawnAndAddCard(cardOneYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_1);
	SpawnAndAddCard(cardTwoYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_2);
	SpawnAndAddCard(cardThreeYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_3);
	SpawnAndAddCard(cardFourYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_4);
	SpawnAndAddCard(cardFiveYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_5);
	SpawnAndAddCard(cardSixYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_6);
	SpawnAndAddCard(cardSevenYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_7);
	SpawnAndAddCard(cardEightYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_8);
	SpawnAndAddCard(cardNineYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_9);
	SpawnAndAddCard(cardSkipYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_Skip);
	SpawnAndAddCard(cardReverseYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_Reverse);
	SpawnAndAddCard(cardDrawTwoYellowMesh, specialDeck, ECardType::CT_Yellow, ECardValue::CV_DrawTwo);

	// Spawn wild cards
	SpawnAndAddCard(cardWildMesh, specialDeck, ECardType::CT_Wild, ECardValue::CV_Wild);
	SpawnAndAddCard(cardWildDrawFourMesh, specialDeck, ECardType::CT_Wild, ECardValue::CV_DrawFour);
}

// Spawn a card actor and add it to the selected deck
void AMainGameModeBase::SpawnAndAddCard(UStaticMesh* cardMesh, TArray<TObjectPtr<ACardActor>>& deck, const ECardType& cardType, const ECardValue& cardValue)
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
	newCard->SetCardType(cardType);
	newCard->SetCardValue(cardValue);
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
void AMainGameModeBase::StartMainGameLoop(AGameStartButton* currGameStartButton)
{
	// If no player world or card mesh return
	if (!playerWorld || !mainCharacter || !character)
	{
		UE_LOG(LogTemp, Display, TEXT("Cannot start game because if (!playerWorld || !mainCharacter || !character) returned true"));
		return;
	}

	// Get the number of players playing the game and start
	UGameplayStatics::GetAllActorsOfClass(playerWorld, mainCharacterClass, mainCharacterActorArray);

	for (AActor* actor : mainCharacterActorArray)
	{
		AMainCharacter* mc = Cast<AMainCharacter>(actor);
		if (mc) mainCharacterArray.Push(mc);
	}
	if (mainCharacterArray.Num() <= 0) return;

	bIsGameRunning = true;
	currGameStartButton->SetGameHasStarted(true);
	cardGameState = ECardGameState::GS_Start;

	// Spawn a card for each player
	UStaticMesh* mesh;
	ACardActor* card;
	AMainCharacter* tempMainCharacter;

	for (int i = 0; i < mainCharacterArray.Num(); ++i)
	{
		for (int j = 0; j < cardsDealtFirst; ++j)
		{
			mesh = GetRandomCardMesh(specialDeck);
			if (!mesh) continue;
			card = SpawnCardActor(mesh, FVector(0, 0, 0));
			tempMainCharacter = mainCharacterArray[i];
			tempMainCharacter->InteractWithCard(card);
		}
	}

	GetWorldTimerManager().SetTimer( timerHandle, this, &AMainGameModeBase::TurnTimerFinished, 5.0f, false);
	UE_LOG(LogTemp, Display, TEXT("Timer started"));

	/*bIsGameRunning = false;
	currGameStartButton->SetGameHasStarted(false);*/

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

// Handle logic for when timer runs out for player ( go to next player and reset timer )
void AMainGameModeBase::TurnTimerFinished()
{
	UE_LOG(LogTemp, Display, TEXT("Timer ran out"));
}
