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

}
