// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CardActor.generated.h"

class AMainCharacter;

// Card type enum
UENUM(BlueprintType)
enum class ECardType : uint8
{
	CT_Club    UMETA(DisplayName = "Club"),
	CT_Spade   UMETA(DisplayName = "Spade"),
	CT_Heart   UMETA(DisplayName = "Heart"),
	CT_Diamond UMETA(DisplayName = "Diamond")
};

// Card value enum
UENUM(BlueprintType)
enum class ECardValue : uint8
{
	CV_2     UMETA(DisplayName = "2"),
	CV_3     UMETA(DisplayName = "3"),
	CV_4     UMETA(DisplayName = "4"),
	CV_5     UMETA(DisplayName = "5"),
	CV_6     UMETA(DisplayName = "6"),
	CV_7     UMETA(DisplayName = "7"),
	CV_8     UMETA(DisplayName = "8"),
	CV_9     UMETA(DisplayName = "9"),
	CV_10    UMETA(DisplayName = "10"),
	CV_Jack  UMETA(DisplayName = "Jack"),
	CV_Queen UMETA(DisplayName = "Queen"),
	CV_King  UMETA(DisplayName = "King"),
	CV_Ace   UMETA(DisplayName = "Ace"),
	CV_Joker UMETA(DisplayName = "Joker")
};

UCLASS()
class CHS_API ACardActor : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Enums --- */
	

	/* --- Methods --- */
	// Sets default values for this actor's properties
	ACardActor();

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

	// Set is card equipped boolean
	void SetIsCardEquipped(bool isEquipped);

	// Player unequip card
	void UnequipCard();


private:
	/* --- Methods --- */
	

	/* --- Variables --- */
	// Is the card equipped by a player
	bool bIsCardEquipped = false;

	// Player equipping the card
	AMainCharacter* owningCharacter;

	// Player card socket
	UStaticMeshComponent* playerCardSocket;

	// Card type (suit/cateogry)
	UPROPERTY(EditDefaultsOnly)
	ECardType cardType;

	// Card value
	ECardValue cardValue;
};
