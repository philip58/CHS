// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
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
		UE_LOG(LogTemp, Display, TEXT("Player World: %s"), *playerWorld->GetName());

		playerController = playerWorld->GetFirstPlayerController();
	}

	// Get main character  
	if (playerController)
	{
		UE_LOG(LogTemp, Display, TEXT("Player Controller: %s"), *playerController->GetName());

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
		UE_LOG(LogTemp, Display, TEXT("Main character: %s"), *mainCharacter->GetName());

		playerMovementComponent = mainCharacter->GetCharacterMovement();
	}

	// Log the player movement component
	if (playerMovementComponent)
	{
		UE_LOG(LogTemp, Display, TEXT("Player movement component: %s"), *playerMovementComponent->GetName());
	}

	
}
