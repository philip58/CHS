// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CardActor.generated.h"

class AMainCharacter;

UCLASS()
class CHS_API ACardActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Methods --- */
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Equip card
	void EquipCard(AMainCharacter* playerCharacter);

	/* --- Variables --- */

	// Card mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UStaticMeshComponent* cardMesh;

	// Card box collision
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UBoxComponent* cardBoxCollision;


private:
	/* --- Methods --- */
	

	/* --- Variables --- */
	// Is the card equipped by a player
	bool bIsCardEquipped = false;

	// Player equipping the card
	AMainCharacter* owningCharacter;
};
