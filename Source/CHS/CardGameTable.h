// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardTypeEnums.h"
#include "CardGameTable.generated.h"

class AGameStartButton;
class ACardTableSlot;
class AMainGameModeBase;
class APlayerChairSlot;
class ATextRenderActor;
class UTextRenderComponent;

UCLASS()
class CHS_API ACardGameTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardGameTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Main card game loop logic
	void StartMainGameLoop(AGameStartButton* currGameStartButton);

	// Boolean for game is still running or not
	bool bIsGameRunning = false;

private:
	/* --- Methods --- */
	// Spawn game start button
	void SpawnGameStartButton();

	// Spawn player chairs
	void SpawnPlayerChairs();

	// Resize the table for more chairs
	void ResizeTable();

	// Handle logic for when the player ran out of time
	void TurnTimerFinished();

	// Wait game state logic
	void WaitForPlayerTurn();

	// Spawn the timer table text
	void SpawnTimerText();

	// Set the timer for the players turn
	void SetPlayerTurnTimer();



	/* --- Variables --- */
	// Place holder root component
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> rootMeshComponent;

	// Card table scene component
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> cardTableMeshComponent;

	// Classs Game start button for spawning
	UPROPERTY(EditDefaultsOnly, Category = "Spawned Actor Classes")
	TSubclassOf<AGameStartButton> gameStartButtonClass;

	// Actor Game start button on the table
	TObjectPtr<AGameStartButton> gameStartButton;

	// Class for Card table slot for spawning
	UPROPERTY(EditDefaultsOnly, Category = "Spawned Actor Classes")
	TSubclassOf<ACardTableSlot> cardTableSlotClass;

	// Class for Card table slot for spawning
	UPROPERTY(EditDefaultsOnly, Category = "Spawned Actor Classes")
	TSubclassOf<APlayerChairSlot> playerChairClass;

	// Map for player chair ID integer and player chair associated with that ID
	TMap<int, TObjectPtr<APlayerChairSlot>> playerChairMap;

	// Number of player chairs for the table
	UPROPERTY(EditDefaultsOnly, Category = "Card table properties | game settings")
	int numberOfChairs = 4;

	// Array for Card table slot actors on the table 
	TArray<TObjectPtr<ACardTableSlot>> cardTableSlot;

	// Pointer for main gamemode base
	TObjectPtr<AMainGameModeBase> mainGameModeBase;

	// Card table default x scale value
	UPROPERTY(EditAnywhere, Category = "Card table properties | Scale")
	float tableDefaultScaleX = 3.25f;

	// Card table default y scale value
	UPROPERTY(EditAnywhere, Category = "Card table properties | Scale")
	float tableDefaultScaleY = 3.25f;

	// Card table default z scale value
	UPROPERTY(EditAnywhere, Category = "Card table properties | Scale")
	float tableDefaultScaleZ = 1.0f;

	// Table size 
	FVector tableSize;

	// button x location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonXSpawnMultiplier = 2;

	// button y location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonYSpawnMultiplier = 2;

	// button z location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonZSpawnMultiplier = 2;

	// button x location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonXSpawnPadding = 20;

	// button y location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonYSpawnPadding = 30;

	// button z location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float buttonZSpawnPadding = 4;

	// chair x location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairXSpawnMultiplier = 2;

	// chair y location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairYSpawnMultiplier = 2;

	// chair z location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairZSpawnMultiplier = 2;

	// chair x location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairXSpawnPadding = 40;

	// chair y location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairYSpawnPadding = 40;

	// chair z location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float chairZSpawnPadding = 35;

	// Current table location
	FVector currTableLocation;

	// Distance between chairs during spawning
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float distanceBetweenChairsIncrement = 40;

	//// Boolean for game is still running or not
	//bool bIsGameRunning = false;

	// Boolean for if first deal of cards to players occured
	bool bHasFirstDealOccured = false;

	// Game state enum for tracking point in match
	ECardGameState cardGameState;

	// Game table timer text actor
	UPROPERTY(EditAnywhere, Category = "Card Game Properties/Settings")
	TObjectPtr<ATextRenderActor> timerTextActor;

	// Timer text component
	TObjectPtr<UTextRenderComponent> timerTextComponent;

	// Table timer text class for spawning
	UPROPERTY(EditAnywhere, Category = "Card Game Properties/Settings")
	TSubclassOf<ATextRenderActor> timerTextClass;

	// Length of timer per turn
	UPROPERTY(EditDefaultsOnly, Category = "Card Game Properties/Settings")
	float turnTimerLength = 10.0f;

	// Length of displaying times up message before next turn
	UPROPERTY(EditDefaultsOnly, Category = "Card Game Properties/Settings")
	float timesUpTimerLength = 3.0f;

	// Number of cards to be dealt in first hand
	UPROPERTY(EditDefaultsOnly, Category = "Card Game Properties/Settings")
	int cardsDealtFirst = 7;

	// Timer handle for game timers
	FTimerHandle timerHandle;

	// timer x location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerXSpawnMultiplier = 2;

	// timer y location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerYSpawnMultiplier = 20;

	// timer z location multiplier 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerZSpawnMultiplier = 2;

	// timer x location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerXSpawnPadding = 0;

	// timer y location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerYSpawnPadding = 0;

	// timer z location padding 
	UPROPERTY(EditAnywhere, Category = "Card Table properties | Scale")
	float timerZSpawnPadding = 40;

	// Current player turn ID 
	int playerTurnID = 1;
};
