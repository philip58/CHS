// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MainGameModeBase.h"
#include "MainCharacter.generated.h"

class ACardActor;
class APlayerChairSlot;
class UPlayerHUD;

UCLASS()
class CHS_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/* --- Methods--- */
	// Sets default values for this character's properties
	AMainCharacter();

	/* --- Variables--- */


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Methods--- */ 
	// Called every frame
	virtual void Tick(float deltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	// Player move forward
	void WalkForward(float input);

	// Player move backwards
	void WalkBackwards(float input);

	// Player move left
	void WalkLeft(float input);

	// Player move right
	void WalkRight(float input);

	// Player jump
	void PlayerJump();

	// Player look horizontally
	void LookHorizontally(float input);

	// Player look horizontally
	void LookVertically(float input);

	// Start player sprinting
	void StartSprinting();

	// Stop player sprinting
	void StopSprinting();

	// Handle interaction with objects (key E)
	void Interact();

	// Throw the equipped object (key Q)
	void Throw();

	// Scroll up method: on scroll up, cycle through the inventory increasingly
	void ScrollUp();
	
	// Scroll down method: on scroll down, cycle through the inventory decreasingly
	void ScrollDown();

	// Toggle inventory, hide/unhide equipped card
	void ToggleCardHide(bool bHide);

	//Interact with actor/card
	void InteractWithCard(AActor* interactedActor);

	// Interact with actor/chair
	void InteractWithChair(AActor* interactedActor);

	// Player leave chair
	void LeaveChair();

	/* --- Variables--- */ 
	// Card placeholder socket
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* cardPlaceHolderSocket;

private:
	/* --- Methods--- */
	//Equip the card
	void EquipCard(ACardActor* cardActor);

	// Unequip the card
	void UnequipCard(ACardActor* cardActor);

	// LineTrace every frame for interactable handling
	AActor* GetLineTraceHitActor();

	// Handle loggic while hovering over an actor
	void HandleHovering(AActor* actor);

	// Handle loggic while hovering over a card
	void CardHover(AActor* hoveredActor);

	// Handle loggic while hovering over a chair
	void ChairHover(AActor* hoveredActor);

	// Increment through the cards up or down
	void IncrementThroughCards(const int& increment);

	// Increment through inventory up or down
	void IncrementThroughInventory(const int& increment);

	/* --- Variables--- */
	// Player camera (viewport)
	UPROPERTY(EditAnywhere, Category = "Player Camera Properties")
	UCameraComponent* playerCamera;

	// Is the player sprinting
	bool bIsPlayerSprinting = false;

	// Gamemode base
	TObjectPtr<AMainGameModeBase> gameModeBase;

	// Line trace length 
	UPROPERTY(EditDefaultsOnly, Category = "Player Camera Properties")
	float lineTraceLength = 100;

	// Line trace start distance from camera
	UPROPERTY(EditDefaultsOnly, Category = "Player Camera Properties")
	float lineTraceStartOffset = 25;

	// Player mesh component
	UPROPERTY(EditDefaultsOnly, Category = "Player Mesh Properties")
	UStaticMeshComponent* playerMesh;

	// Player sprint speed
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement Properties")
	float sprintSpeed = 400;

	// Player walk speed
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement Properties")
	float walkSpeed = 200;

	// Player air control 
	UPROPERTY(EditDefaultsOnly, Category = "Player Movement Properties")
	float airControl = .1;
	
	// Equipped card
	ACardActor* equippedCard;

	// Hash map of all card the player has and a corresponding boolean to represent if card is currently selected or not
	TArray<TObjectPtr<ACardActor>> cardsInInventory;

	// Throw velocity
	UPROPERTY(EditDefaultsOnly, Category = "Card Properties")
	float throwVelocity = 10.0;

	// Throw height
	UPROPERTY(EditDefaultsOnly, Category = "Card Properties")
	float throwHeight = 10.0;

	// Counter to hold the position of which card is equipped
	int equippedCardPos = -1;

	// Chair that player is sitting in
	APlayerChairSlot* playerChair;

	// Boolean if player is sitting
	bool bIsPlayerSitting = false;

	// Distance to move away from chair after exiting
	UPROPERTY(EditAnywhere)
	float distanceFromChair = 10.0f;

	// Player offset when sitting in chair
	UPROPERTY(EditAnywhere)
	float chairSitOffset = 10.0f;

	// Player velocity when exiting in chair
	UPROPERTY(EditAnywhere)
	float chairExitVelocity = 10.0f;

	// Actor in view hit by line trace during tick function
	AActor* actorInView;

	// Player HUD
	UPlayerHUD* playerHUD;

	// Boolean if card is hidden or not
	bool bIsCardVisible = true;

	// Card image png for inventory
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Images")
	UTexture2D* cardInventoryImg;

	// Blank image png for clearing inventory img
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Images")
	UTexture2D* blankInventoryImg;

	// Red (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float rDefaultColorInventorySlot = .015f;

	// Green (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float gDefaultColorInventorySlot = .015f;

	// Blue (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float bDefaultColorInventorySlot = .015f;

	// Opacity (RBGA) in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float aDefaultColorInventorySlot = .2f;

	// Red (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float rSelectedColorInventorySlot = 1.0f;

	// Green (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float gSelectedColorInventorySlot = 1.0f;

	// Blue (RBGA) color in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float bSelectedColorInventorySlot = 1.0f;

	// Opacity (RBGA) in the inventory slot background
	UPROPERTY(EditDefaultsOnly, Category = "Inventory Attributes")
	float aSelectedColorInventorySlot = .6f;

	// Inventory size
	int inventorySize = 0;

	// Inventory position
	int inventoryPos = 0;

};
