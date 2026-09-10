// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PlayerChairSlot.generated.h"

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

private:
	/* --- Methods --- */

	/* --- Variables --- */
	// Boolean if chair has someone sitting in it
	bool bIsSatIn = false;
};
