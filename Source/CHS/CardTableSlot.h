// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CardTableSlot.generated.h"

UCLASS()
class CHS_API ACardTableSlot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACardTableSlot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/* --- Methods --- */
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* --- Variables --- */
	// Box collision for triggger
	UPROPERTY(EditAnywhere)
	UBoxComponent* triggerCollision;

	// Collision scale
	UPROPERTY(EditAnywhere)
	float collisionScale = .5f;

};
