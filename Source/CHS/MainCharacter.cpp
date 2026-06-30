// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up player camera and its properties 
	// Create component, attach to root, use pawn rotation
	playerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	playerCamera->SetupAttachment(RootComponent);
	playerCamera->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

	// Bind axis mappings (walk up, walk down, walk left, walk right, look vertically, look horizontally)
	playerInputComponent->BindAxis("WalkForward", this, &AMainCharacter::WalkForward);
	playerInputComponent->BindAxis("WalkBackwards", this, &AMainCharacter::WalkBackwards);
	playerInputComponent->BindAxis("WalkLeft", this, &AMainCharacter::WalkLeft);
	playerInputComponent->BindAxis("WalkRight", this, &AMainCharacter::WalkRight);
	playerInputComponent->BindAxis("LookHorizontally", this, &AMainCharacter::LookHorizontally);
	playerInputComponent->BindAxis("LookVertically", this, &AMainCharacter::LookVertically);

	// Bind action mappings (jump)
	playerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainCharacter::PlayerJump);
}

// Move the player forward
void AMainCharacter::WalkForward(float input )
{
	AddMovementInput(GetActorForwardVector(), input);
}

// Move the player backwards
void AMainCharacter::WalkBackwards(float input)
{
	AddMovementInput(GetActorForwardVector(), -input);
}

// Move the player left
void AMainCharacter::WalkLeft(float input)
{
	AddMovementInput(GetActorRightVector(), -input);
}

// Move the player right
void AMainCharacter::WalkRight(float input)
{
	AddMovementInput(GetActorRightVector(), input);
}

// Player jump
void AMainCharacter::PlayerJump()
{
	if(CanJump())
	{
		Jump();
	}
}

void AMainCharacter::LookHorizontally(float input)
{
	AddControllerYawInput(input);
}

void AMainCharacter::LookVertically(float input)
{
	AddControllerPitchInput(-input);
}
