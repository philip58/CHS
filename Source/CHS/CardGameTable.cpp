// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameTable.h"
#include "Components/ShapeComponent.h"
#include "CardTableSlot.h"
#include "GameStartButton.h"
#include "MainGameModeBase.h"
#include "PlayerChairSlot.h"

// Sets default values
ACardGameTable::ACardGameTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up the table scene component and root component
	rootMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Placeholder Root Component"));
	SetRootComponent(rootMeshComponent);
	cardTableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Table Component"));
	cardTableMeshComponent->SetupAttachment(RootComponent);
	cardTableMeshComponent->SetRelativeScale3D(FVector(tableDefaultScaleX, tableDefaultScaleY, tableDefaultScaleZ));
	cardTableMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

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
	}

}

// Called every frame
void ACardGameTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

	// Loop through for each chair and spawn/append to chair actor array
	for (int i = 1; i <= numberOfChairs; ++i)
	{
		if (i % 4 == 0)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector( ( tableSize.X / chairXSpawnMultiplier ) + chairXSpawnPadding, chairDistanceFromNeighbor, chairZSpawnPadding ));
		}
		else if (i % 4 == 1)
		{
			if (i != 1)
			{
				chairDistanceFromNeighbor += distanceBetweenChairsIncrement;
				ResizeTable();
			}
			chairNewTransform.SetLocation(currTableLocation + FVector( chairDistanceFromNeighbor, ( tableSize.Y / chairXSpawnMultiplier ) + chairYSpawnPadding, chairZSpawnPadding ));
		}
		else if (i % 4 == 2)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector( ( - tableSize.X / chairXSpawnMultiplier ) - chairXSpawnPadding, -chairDistanceFromNeighbor, chairZSpawnPadding));
		}
		else if (i % 4 == 3)
		{
			chairNewTransform.SetLocation(currTableLocation + FVector( - chairDistanceFromNeighbor, ( - tableSize.Y / chairXSpawnMultiplier ) - chairYSpawnPadding, chairZSpawnPadding));
		}


		// Spawn the chair actor, rotate it, and append to the chairs array
		spawnedPlayerChair = mainGameModeBase->playerWorld->SpawnActor<APlayerChairSlot>(playerChairClass, chairNewTransform, chairSpawnParams);
		spawnedPlayerChair->SetActorRelativeRotation(FRotator(-90, 0, 0));
		playerChairArray.Push(spawnedPlayerChair);

	}
}

void ACardGameTable::ResizeTable()
{
	UE_LOG(LogTemp, Display, TEXT("Resizing table"));
}

