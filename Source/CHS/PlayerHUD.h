// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UImage;

UCLASS()
class CHS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    /* --- Methods --- */
    UFUNCTION(BlueprintCallable)
    void SetInteractPopupText(const FString& name);

    UFUNCTION(BlueprintCallable)
    void SetInventoryImage(UImage* currInventoryImage, UImage* newInventoryImage, const float& opacity);

    /* --- Variables --- */
    // HUD popup text 
    UPROPERTY(meta = (BindWidget))
    class UTextBlock* interactPopupText;

    // HUD inventory image 1
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage1;

    // HUD inventory image 2
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage2;

    // HUD inventory image 3
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage3;

    // HUD inventory image 4
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage4;

    // HUD inventory image 5
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage5;

    // HUD inventory image 6
    UPROPERTY(meta = (BindWidget))
    class UImage* inventoryImage6;

};
