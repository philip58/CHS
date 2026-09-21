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
	void PopulateDeck();

	// Spawn card and add it to deck
	void SpawnAndAddCard(UStaticMesh* cardMesh);

	// Spawn a card
	void SpawnCardActor();

	/* --- Variables --- */
	// Globally accessible character movement component
	UPROPERTY(BlueprintReadOnly, Category = "Character Properties")
	TObjectPtr<UCharacterMovementComponent> playerMovementComponent;

	// Globally accessible world 
	TObjectPtr<UWorld> playerWorld;

	// Globally accessible player controller
	TObjectPtr<APlayerController> playerController;

	// Globally accessible character
	TObjectPtr<ACharacter> mainCharacter;

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
	TArray< TObjectPtr<ACardActor>> cardDeck;

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

	// Counter for offeset of spawning cards
	int spawnOffsetCounter = 0;
};
