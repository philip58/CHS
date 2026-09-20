// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MainGameModeBase.generated.h"

class UPlayerHUD;
class UImage;
class UBorder;

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
};
