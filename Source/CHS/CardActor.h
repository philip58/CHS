// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CardActor.generated.h"

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

	/* --- Variables --- */

	// Card mesh
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UStaticMeshComponent* cardMesh;

	// Card box collision
	UPROPERTY(EditDefaultsOnly, Category = "Card Mesh Properties")
	UBoxComponent* cardBoxCollision;
};
