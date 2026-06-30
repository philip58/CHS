// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CHS_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public: 
	// Constructor for game mode
	AMainGameModeBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
