// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerChairSlot.generated.h"

class AMainCharacter;
class UTextRenderComponent;
class ATextRenderActor;

UCLASS()
class CHS_API APlayerChairSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerChairSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Methods --- */
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Getter for chair sat in boolean
	bool GetIsSatIn() const;

	// Setter for chair sat in boolean
	void SetIsSatIn(bool bSatBool);

	/* --- Variables --- */
	// Box collision for triggger
	UPROPERTY(EditAnywhere)
	UBoxComponent* triggerCollision;

	// Collision scale
	UPROPERTY(EditAnywhere)
	float collisionScale = .5f;

	// Static mesh component for the chair
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* chair;

	// Get the character sitting in the chair
	TObjectPtr<AMainCharacter> GetCharacterInChair() const;

	// Set the character sitting in the chair
	void SetCharacterInChair(TObjectPtr<AMainCharacter> character);

	// Set chair text
	void SetChairText(const FString& str);

	// Highlight chair text 
	void HighlightChairText();

	// Highlight chair text 
	void UnHighlightChairText();
private:
	/* --- Methods --- */

	/* --- Variables --- */
	// Boolean if chair has someone sitting in it
	bool bIsSatIn = false;

	// Main character sitting in the chair
	TObjectPtr<AMainCharacter> characterInChair;

	// Text actor for player chair
	UPROPERTY(EditAnywhere)
	TObjectPtr<ATextRenderActor> textActor;

	// Text component for player chair
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextRenderComponent> textComponent;

	// Chair text x padding
	UPROPERTY(EditAnywhere)
	float chairTextXPadding = 200;

	// Chair text z padding
	UPROPERTY(EditAnywhere)
	float chairTextYPadding = 0;

	// Chair text z padding
	UPROPERTY(EditAnywhere)
	float chairTextZPadding = 0;

	// Highlighted text material when player's turn
	UPROPERTY(EditAnywhere)
	UMaterialInterface* highlightMaterial;

	// Unhighlighted text material when not player's turn
	UPROPERTY(EditAnywhere)
	UMaterialInterface* unHighlightMaterial;
};
