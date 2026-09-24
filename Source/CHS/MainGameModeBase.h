// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainGameModeBase.generated.h"

class UPlayerHUD;
class UImage;
class UBorder;
class ACardActor;
class AMainCharacter;

/**
 * 
 */
UCLASS()
class CHS_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	/* --- Methods --- */
	// Constructor for game mode
	AMainGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Add inventory widgets to arrays
	void PopulateInventoryImageSlotArray();

	// Populate cards to deck array
	void PopulateDecks();

	// Spawn card and add it to deck
	void SpawnAndAddCard(UStaticMesh* cardMesh, TArray<TObjectPtr<ACardActor>>& deck);

	// Spawn a card at given location and return the card
	ACardActor* SpawnCardActor(UStaticMesh* cardMesh, const FVector& location);

	// Main card game loop logic
	void MainGameLoop();

	// Get random card mesh from card array
	UStaticMesh* GetRandomCardMesh(const TArray<TObjectPtr<ACardActor>>& deckArray);

	/* --- Variables --- */
	// Globally accessible character movement component
	UPROPERTY(BlueprintReadOnly, Category = "Character Properties")
	TObjectPtr<UCharacterMovementComponent> playerMovementComponent;

	// Globally accessible world 
	TObjectPtr<UWorld> playerWorld;

	// Globally accessible player controller
	TObjectPtr<APlayerController> playerController;

	// Globally accessible character
	TObjectPtr<ACharacter> character;

	// Globally accessible ui
	TObjectPtr<UPlayerHUD> playerHUD;

	// Class object of UPlayerHUD
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPlayerHUD> playerHUDClass;

	// Array of inventory images
	TArray<TObjectPtr<UImage>> inventoryImageArray;

	// Array of inventory slots
	TArray<TObjectPtr<UBorder>> inventorySlotArray;

	// Array of a deck of cards
	TArray<TObjectPtr<ACardActor>> cardDeck;

	// Array of a special deck of cards
	TArray<TObjectPtr<ACardActor>> specialDeck;

	// Card actor class
	UPROPERTY(EditDefaultsOnly, Category = "Card Class")
	TSubclassOf<ACardActor> cardActorClass;

	/* --- Card Meshes --- */
	// Card ace of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardAceDiamondsMesh;

	// Card two of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardTwoDiamondsMesh;

	// Card three of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardThreeDiamondsMesh;

	// Card four of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardFourDiamondsMesh;

	// Card five of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardFiveDiamondsMesh;

	// Card six of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardSixDiamondsMesh;

	// Card seven of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardSevenDiamondsMesh;

	// Card eight of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardEightDiamondsMesh;

	// Card nine of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardNineDiamondsMesh;

	// Card ten of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardTenDiamondsMesh;

	// Card jack of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardJackDiamondsMesh;

	// Card queen of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardQueenDiamondsMesh;

	// Card king of diamonds mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Diamonds")
	UStaticMesh* cardKingDiamondsMesh;

	// Card ace of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardAceHeartsMesh;

	// Card two of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardTwoHeartsMesh;

	// Card three of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardThreeHeartsMesh;

	// Card four of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardFourHeartsMesh;

	// Card five of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardFiveHeartsMesh;

	// Card six of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardSixHeartsMesh;

	// Card seven of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardSevenHeartsMesh;

	// Card eight of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardEightHeartsMesh;

	// Card nine of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardNineHeartsMesh;

	// Card ten of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardTenHeartsMesh;

	// Card jack of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardJackHeartsMesh;

	// Card queen of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardQueenHeartsMesh;

	// Card king of hearts mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Hearts")
	UStaticMesh* cardKingHeartsMesh;

	// Card ace of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardAceClubsMesh;

	// Card two of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardTwoClubsMesh;

	// Card three of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardThreeClubsMesh;

	// Card four of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardFourClubsMesh;

	// Card five of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardFiveClubsMesh;

	// Card six of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardSixClubsMesh;

	// Card seven of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardSevenClubsMesh;

	// Card eight of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardEightClubsMesh;

	// Card nine of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardNineClubsMesh;

	// Card ten of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardTenClubsMesh;

	// Card jack of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardJackClubsMesh;

	// Card queen of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardQueenClubsMesh;

	// Card king of clubs mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Clubs")
	UStaticMesh* cardKingClubsMesh;

	// Card ace of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardAceSpadesMesh;

	// Card two of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardTwoSpadesMesh;

	// Card three of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardThreeSpadesMesh;

	// Card four of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardFourSpadesMesh;

	// Card five of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardFiveSpadesMesh;

	// Card six of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardSixSpadesMesh;

	// Card seven of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardSevenSpadesMesh;

	// Card eight of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardEightSpadesMesh;

	// Card nine of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardNineSpadesMesh;

	// Card ten of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardTenSpadesMesh;

	// Card jack of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardJackSpadesMesh;

	// Card queen of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardQueenSpadesMesh;

	// Card king of spades mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Spades")
	UStaticMesh* cardKingSpadesMesh;

	// Card red joker mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Jokers")
	UStaticMesh* cardRedJokerMesh;

	// Card black joker mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Jokers")
	UStaticMesh* cardBlackJokerMesh;

	/* --- End of Card Meshes --- */

	// Counter for offeset of spawning cards
	int spawnOffsetCounter = 0;

	/* --- Begin of special card meshes --- */

	// Red cards
	// Card zero of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardZeroRedMesh;

	// Card one of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardOneRedMesh;

	// Card two of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardTwoRedMesh;

	// Card three of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardThreeRedMesh;

	// Card four of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardFourRedMesh;

	// Card five of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardFiveRedMesh;

	// Card six of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardSixRedMesh;

	// Card seven of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardSevenRedMesh;

	// Card eight of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardEightRedMesh;

	// Card nine of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardNineRedMesh;

	// Card skip of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardSkipRedMesh;

	// Card reverse of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardReverseRedMesh;

	// Card draw two of red mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Red")
	UStaticMesh* cardDrawTwoRedMesh;


	// Blue cards
	// Card zero of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardZeroBlueMesh;

	// Card one of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardOneBlueMesh;

	// Card two of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardTwoBlueMesh;

	// Card three of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardThreeBlueMesh;

	// Card four of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardFourBlueMesh;

	// Card five of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardFiveBlueMesh;

	// Card six of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardSixBlueMesh;

	// Card seven of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardSevenBlueMesh;

	// Card eight of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardEightBlueMesh;

	// Card nine of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardNineBlueMesh;

	// Card skip of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardSkipBlueMesh;

	// Card reverse of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardReverseBlueMesh;

	// Card draw two of blue mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Blue")
	UStaticMesh* cardDrawTwoBlueMesh;


	// Green cards
	// Card zero of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardZeroGreenMesh;

	// Card one of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardOneGreenMesh;

	// Card two of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardTwoGreenMesh;

	// Card three of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardThreeGreenMesh;

	// Card four of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardFourGreenMesh;

	// Card five of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardFiveGreenMesh;

	// Card six of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardSixGreenMesh;

	// Card seven of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardSevenGreenMesh;

	// Card eight of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardEightGreenMesh;

	// Card nine of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardNineGreenMesh;

	// Card skip of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardSkipGreenMesh;

	// Card reverse of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardReverseGreenMesh;

	// Card draw two of green mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Green")
	UStaticMesh* cardDrawTwoGreenMesh;


	// Yellow cards
	// Card zero of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardZeroYellowMesh;

	// Card one of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardOneYellowMesh;

	// Card two of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardTwoYellowMesh;

	// Card three of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardThreeYellowMesh;

	// Card four of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardFourYellowMesh;

	// Card five of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardFiveYellowMesh;

	// Card six of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardSixYellowMesh;

	// Card seven of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardSevenYellowMesh;

	// Card eight of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardEightYellowMesh;

	// Card nine of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardNineYellowMesh;

	// Card skip of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardSkipYellowMesh;

	// Card reverse of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardReverseYellowMesh;

	// Card draw two of yellow mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Yellow")
	UStaticMesh* cardDrawTwoYellowMesh;


	// Wild cards
	// Card wild mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Wilds")
	UStaticMesh* cardWildMesh;

	// Card wild draw four mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Meshes|Wilds")
	UStaticMesh* cardWildDrawFourMesh;

	/* --- End of special card meshes --- */

	// Integer of number of players for a table
	UPROPERTY(EditDefaultsOnly, Category = "Card Game Properties/Settings")
	int numPlayers = 1;

	// Integer of timer per turn
	UPROPERTY(EditDefaultsOnly, Category = "Card Game Properties/Settings")
	float timerLength = 10.0f;

	// Timer handle for game timers
	FTimerHandle* timerHandle;

	// Main character class
	UPROPERTY(EditAnywhere, Category = "Card Game Properties/Settings")
	TSubclassOf<AMainCharacter> mainCharacterClass;

	// Main character pointer
	TObjectPtr<AMainCharacter> mainCharacter;

	// Array of main character actors
	TArray<AActor*> mainCharacterActorArray;

	// Array of main characters
	TArray<TObjectPtr<AMainCharacter>> mainCharacterArray;

	// Boolean for game is still running or not
	bool bIsGameRunning = false;

	// Boolean for if first deal of cards to players occured
	bool bHasFirstDealOccured = false;
};
