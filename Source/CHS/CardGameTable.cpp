// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameTable.h"
#include "Components/ShapeComponent.h"
#include "CardTableSlot.h"
#include "GameStartButton.h"
#include "MainGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"
#include "CardActor.h"
#include "Engine/TextRenderActor.h"
#include "Components/TextRenderComponent.h"
#include "PlayerChairSlot.h"

// Sets default values
ACardGameTable::ACardGameTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the root component, table scene component, and timer text component 
	rootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placeholder Root Component"));
	SetRootComponent(rootMeshComponent);
	cardTableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Table Component"));
	cardTableMeshComponent->SetupAttachment(RootComponent);
	cardTableMeshComponent->SetRelativeScale3D(FVector(tableDefaultScaleX, tableDefaultScaleY, tableDefaultScaleZ));
	cardTableMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	//timerTextActor = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Timer Text Component"));
	//timerTextActor->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACardGameTable::BeginPlay()
{
	Super::BeginPlay();

	// Get temporary world variable and use it to set the gamemode base to the custom MainGameModeBase
	TWeakObjectPtr<UWorld> tempWorld = GetWorld();
	if (tempWorld != nullptr)
	{
		try
		{
			mainGameModeBase = Cast<AMainGameModeBase>(tempWorld->GetAuthGameMode());
		}
		catch (const std::exception&)
		{
			UE_LOG(LogTemp, Display, TEXT("Casting gamemode to AMainGameMode failed"));
		}
	}

	// Store table size for actor spawning
	if (cardTableMeshComponent)
	{
		tableSize = cardTableMeshComponent->Bounds.BoxExtent * 2.0f;
	}

	// Spawn actors (game start button, player chairs)
	if (mainGameModeBase && mainGameModeBase->playerWorld)
	{
		currTableLocation = this->GetActorLocation();
		SpawnGameStartButton();
		SpawnPlayerChairs();
		SpawnTimerText();
	}

}

// Called every frame
void ACardGameTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If game state is in waiting for player move, call wait state function logic
	if (cardGameState == ECardGameState::GS_Wait)
	{
		WaitForPlayerTurn();
	}
	else if (cardGameState == ECardGameState::GS_Done)
	{
		//PlayerTurnDone();
	}

}

// Spawn the game start button
void ACardGameTable::SpawnGameStartButton()
{
	// Setting properties for button actor spawning
	FTransform buttonNewTransform = FTransform::Identity;
	FActorSpawnParameters buttonSpawnParams;
	buttonSpawnParams.Owner = this;
	buttonNewTransform.SetLocation(currTableLocation
		+ 
		FVector( 
			( - tableSize.X / buttonXSpawnMultiplier) + buttonXSpawnPadding,
			( - tableSize.Y / buttonYSpawnMultiplier) + buttonYSpawnPadding,
			( tableSize.Z / buttonZSpawnMultiplier) + buttonZSpawnPadding)
	);
	
	// Spawn the button actor and rotate it correctly
	gameStartButton = mainGameModeBase->playerWorld->SpawnActor<AGameStartButton>(gameStartButtonClass, buttonNewTransform, buttonSpawnParams);
	gameStartButton->SetActorRelativeRotation(FRotator(0, -180, 0));
}

// Spawn the player chairs around the table
void ACardGameTable::SpawnPlayerChairs()
{
	// Setting properties for chair actor spawning
	APlayerChairSlot* spawnedPlayerChair;
	FTransform chairNewTransform; 
	FActorSpawnParameters chairSpawnParams;
	chairSpawnParams.Owner = this;
	chairNewTransform = FTransform::Identity;
	float chairDistanceFromNeighbor = 0;
	float rotationZ = 0;

	// Loop through for each chair and spawn/append to chair actor array
	for (int i = 1; i <= numberOfChairs; ++i)
	{
		if (i % 4 == 0)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector(chairDistanceFromNeighbor, (tableSize.Y / chairXSpawnMultiplier) + chairYSpawnPadding, chairZSpawnPadding));
			rotationZ = -90;
		}
		else if (i % 4 == 1)
		{
			if (i != 1)
			{
				chairDistanceFromNeighbor += distanceBetweenChairsIncrement;
				ResizeTable();
			}
			chairNewTransform.SetLocation(currTableLocation + FVector( ( - tableSize.X / chairXSpawnMultiplier ) - chairXSpawnPadding, -chairDistanceFromNeighbor, chairZSpawnPadding));
		}
		else if (i % 4 == 2)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector(-chairDistanceFromNeighbor, (-tableSize.Y / chairXSpawnMultiplier) - chairYSpawnPadding, chairZSpawnPadding));
			rotationZ = 90;
		}
		else if (i % 4 == 3)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector((tableSize.X / chairXSpawnMultiplier) + chairXSpawnPadding, chairDistanceFromNeighbor, chairZSpawnPadding));
			rotationZ = 180;
		}


		// Spawn the chair actor, rotate it, and append to the chairs array
		spawnedPlayerChair = mainGameModeBase->playerWorld->SpawnActor<APlayerChairSlot>(playerChairClass, chairNewTransform, chairSpawnParams);
		spawnedPlayerChair->SetActorRelativeRotation(FRotator(-90, 0, rotationZ));
		playerChairMap.Add(i, spawnedPlayerChair);

	}
}

void ACardGameTable::ResizeTable()
{
	UE_LOG(LogTemp, Display, TEXT("Resizing table"));
}

// Main card game loop logic
void ACardGameTable::StartMainGameLoop(AGameStartButton* currGameStartButton)
{
	// If no player world or card mesh return
	if (!mainGameModeBase || !mainGameModeBase->playerWorld || !mainGameModeBase->mainCharacter || !mainGameModeBase->character)
	{
		UE_LOG(LogTemp, Display, TEXT("Cannot start game, Func: StartMainGameLoop"));
		return;
	}

	// Get the number of players playing the game and start
	if (mainGameModeBase->mainCharacterActorArray.Num() > 0)
	{
		mainGameModeBase->mainCharacterActorArray.Empty();
	}

	UGameplayStatics::GetAllActorsOfClass(mainGameModeBase->playerWorld, mainGameModeBase->mainCharacterClass, mainGameModeBase->mainCharacterActorArray);

	for (int i = 0; i < mainGameModeBase->mainCharacterActorArray.Num(); ++i)
	{
		AMainCharacter* mc = Cast<AMainCharacter>(mainGameModeBase->mainCharacterActorArray[i]);
		if (mc) mainGameModeBase->mainCharacterArray.Push(mc);
		if (!playerChairMap[i + 1]) continue;

		// For each player that is not the main character, assign them a chair for turn swapping logic
		if (i != 0)
		{
			playerChairMap[i+1]->SetCharacterInChair(mc);
			playerChairMap[i+1]->SetIsSatIn(true);
		}

		// Set player id text for each chair
		FString newChairStr = "Player " + FString::FromInt(i + 1);
		playerChairMap[i + 1]->SetChairText(newChairStr);
	}
	if (mainGameModeBase->mainCharacterArray.Num() <= 0) return;

	bIsGameRunning = true;
	currGameStartButton->SetGameHasStarted(true);
	cardGameState = ECardGameState::GS_Start;

	// Spawn a card for each player
	UStaticMesh* mesh;
	ACardActor* card;
	AMainCharacter* tempMainCharacter;

	for (int i = 0; i < mainGameModeBase->mainCharacterArray.Num(); ++i)
	{
		for (int j = 0; j < cardsDealtFirst; ++j)
		{
			mesh = mainGameModeBase->GetRandomCardMesh(mainGameModeBase->specialDeck);
			if (!mesh) continue;
			card = mainGameModeBase->SpawnCardActor(mesh, FVector(0, 0, 0));
			tempMainCharacter = mainGameModeBase->mainCharacterArray[i];
			tempMainCharacter->InteractWithCard(card);
		}
	}

	int startingPlayerID = FMath::Floor(FMath::RandRange(1,numberOfChairs));
	playerTurnID = startingPlayerID;

	SetPlayerTurnTimer();

	/*bIsGameRunning = false;
	currGameStartButton->SetGameHasStarted(false);*/

}

// Handle logic for when timer runs out for player ( go to next player and reset timer )
void ACardGameTable::TurnTimerFinished()
{
	UE_LOG(LogTemp, Display, TEXT("Timer ran out"));
	cardGameState = ECardGameState::GS_Done;
	if (timerTextComponent) timerTextComponent->SetText(FText::FromString("Time's up!"));
	if (!playerChairMap[playerTurnID]) return;
	playerChairMap[playerTurnID]->UnHighlightChairText();
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACardGameTable::SetPlayerTurnTimer, timesUpTimerLength, false);
}

// Set player turn wait timer 
void ACardGameTable::SetPlayerTurnTimer()
{
	// If there was a previous turn that ran out of time, make that player draw a card
	if (cardGameState == ECardGameState::GS_Done)
	{
		UStaticMesh* mesh;
		ACardActor* card;
		AMainCharacter* tempMainCharacter;
		mesh = mainGameModeBase->GetRandomCardMesh(mainGameModeBase->specialDeck);
		if (mesh)
		{
			card = mainGameModeBase->SpawnCardActor(mesh, FVector(0, 0, 0));
			tempMainCharacter = playerChairMap[playerTurnID]->GetCharacterInChair();
			tempMainCharacter->InteractWithCard(card);
		}

		// Increment the turn to the next player
		if (playerTurnID == numberOfChairs)
		{
			playerTurnID = 1;
		}
		else
		{
			++playerTurnID;
		}
	}

	// Set the timer for the next turn length and highlight current turn player text
	if (!playerChairMap[playerTurnID]) return;
	playerChairMap[playerTurnID]->HighlightChairText();
	GetWorldTimerManager().SetTimer(timerHandle, this, &ACardGameTable::TurnTimerFinished, turnTimerLength, false);
	cardGameState = ECardGameState::GS_Wait;
}

// Called when waiting on player's turn
void ACardGameTable::WaitForPlayerTurn()
{
	float timerText = GetWorldTimerManager().GetTimerRemaining(timerHandle);
	timerText = FMath::Floor(timerText * 10) / 10.0f;
	if(timerTextComponent) timerTextComponent->SetText(FText::AsNumber(timerText));
}

// Spawn the timer text on the table in begin play
void ACardGameTable::SpawnTimerText()
{
	// Setting properties for timer actor spawning
	FTransform timerNewTransform = FTransform::Identity;
	FActorSpawnParameters timerSpawnParams;
	timerSpawnParams.Owner = this;
	timerNewTransform.SetLocation(currTableLocation
		+
		FVector(
			//(-tableSize.X / timerXSpawnMultiplier) + timerXSpawnPadding,
			0,
			(-tableSize.Y / timerYSpawnMultiplier) + timerYSpawnPadding,
			(tableSize.Z / timerZSpawnMultiplier) + timerZSpawnPadding)
	);

	// Spawn the timer actor and rotate it correctly
	timerTextActor = mainGameModeBase->playerWorld->SpawnActor<ATextRenderActor>(timerTextClass, timerNewTransform, timerSpawnParams);
	timerTextActor->SetActorRelativeRotation(FRotator(0, -180, 0));
	if (timerTextActor) timerTextComponent = timerTextActor->GetTextRender();
	if (timerTextComponent) timerTextComponent->SetText(FText::FromString("Press The Start Game Button To Start"));
}
