// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "MainGameModeBase.h"
#include "MainCharacter.generated.h"

class ACardActor;

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
	
	/* --- Variables--- */ 
	// Card placeholder socket
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* cardPlaceHolderSocket;

private:
	/* --- Methods--- */

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

	// Throw velocity
	UPROPERTY(EditDefaultsOnly, Category = "Card Properties")
	float throwVelocity = 10.0;

	// Throw height
	UPROPERTY(EditDefaultsOnly, Category = "Card Properties")
	float throwHeight = 10.0;


};
