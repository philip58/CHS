// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UImage;
class UBorder;

UCLASS()
class CHS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    /* --- Methods --- */
    // Set the text for the pop up interact text HUD widget
    UFUNCTION(BlueprintCallable)
    void SetInteractPopupText(const FString& name);

    // Set the image for the inventory image HUD widget
    UFUNCTION(BlueprintCallable)
    void SetInventoryImage(UImage* currInventoryImage, UTexture2D* newInventoryImage, const float& opacity);

    // Set the color for the inventory slot HUD widget
    UFUNCTION(BlueprintCallable)
    void SetInventorySlotColor(UBorder* inventorySlot, float rColor, float gColor, float bColor, float aColor);

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

    // HUD inventory slot 1
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot1;

    // HUD inventory slot 2
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot2;

    // HUD inventory slot 3
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot3;

    // HUD inventory slot 4
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot4;

    // HUD inventory slot 5
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot5;

    // HUD inventory slot 6
    UPROPERTY(meta = (BindWidget))
    class UBorder* inventorySlot6;

};
