// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStartButton.generated.h"

class UBoxComponent;

UCLASS()
class CHS_API AGameStartButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameStartButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/* --- Methods --- */


	/* --- Variables --- */
	UPROPERTY(EditAnywhere)
	UBoxComponent* boxCollisionComponent;

	// Button mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* buttonMeshComponent;

};
