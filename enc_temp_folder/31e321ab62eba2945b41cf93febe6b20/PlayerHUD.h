// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CHS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void SetInteractPopupText(const FString& name);

protected:
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* interactPopupText;
	
};
