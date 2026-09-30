// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CardTypeEnums.h"
#include "CardActor.generated.h"

class AMainCharacter;
class UBoxComponent;

UCLASS()
class CHS_API ACardActor : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Methods --- */
	// Sets default values for this actor's properties
	ACardActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Equip card
	void EquipCard(AMainCharacter* playerCharacter);

	// Place the card in the given slot
	void PlaceCardInTableSlot(AActor* actor);

	// Set is card equipped boolean
	void SetIsCardEquipped(const bool& isEquipped);

	// Player unequip card
	void UnequipCard();

	// Set new card mesh
	void SetCardMesh(UStaticMesh* newCardMesh);

	/* --- Variables --- */

	// Card mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UStaticMeshComponent* cardMesh;

	// Card box collision
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UBoxComponent* cardBoxCollision;

	// Set the card type
	void SetCardType(const ECardType& newCardType);

	// Set the card value
	void SetCardValue(const ECardValue& newCardValue);

	// Get the card type
	ECardType GetCardType() const;

	// Get the card value
	ECardValue GetCardValue() const;
private:
	/* --- Methods --- */
	// Overlap collision method
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

	// Vertical offset above the table card slot 
	UPROPERTY(EditAnywhere)
	float tableSlotVertOffset = 30.0f;
};
