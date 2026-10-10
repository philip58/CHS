// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UImage;
class UBorder;
class UButton;
class UTextBlock;

UCLASS()
class CHS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

public:
    /* --- Methods --- */
    // Constructor 
    virtual void NativeConstruct() override;

    // Set the text for the pop up interact text HUD widget
    UFUNCTION(BlueprintCallable)
    void SetInteractPopupText(const FString& name);

    // Set the image for the inventory image HUD widget
    UFUNCTION(BlueprintCallable)
    void SetHUDImage(UImage* currImage, UTexture2D* newImage, const float& opacity);

    // Set the opacity for the HUD widget
    UFUNCTION(BlueprintCallable)
    void SetHUDOpacity(UImage* currImage, const float& opacity);

    // Set the color for the inventory slot HUD widget
    UFUNCTION(BlueprintCallable)
    void SetInventorySlotColor(UBorder* inventorySlot, float rColor, float gColor, float bColor, float aColor);

    // Quit on button click
    UFUNCTION(BlueprintCallable)
    void Quit();

    /* --- Variables --- */
    // HUD popup text 
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> interactPopupText;

    // HUD inventory image 1
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage1;

    // HUD inventory image 2
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage2;

    // HUD inventory image 3
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage3;

    // HUD inventory image 4
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage4;

    // HUD inventory image 5
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage5;

    // HUD inventory image 6
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> inventoryImage6;

    // HUD inventory slot 1
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot1;

    // HUD inventory slot 2
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot2;

    // HUD inventory slot 3
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot3;

    // HUD inventory slot 4
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot4;

    // HUD inventory slot 5
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot5;

    // HUD inventory slot 6
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlot6;

    // HUD cross hair
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> crossHair;

    // HUD inventory slot Inner 1
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner1;

    // HUD inventory slot Inner 2
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner2;

    // HUD inventory slot Inner 3
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner3;

    // HUD inventory slot Inner 4
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner4;

    // HUD inventory slot Inner 5
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner5;

    // HUD inventory slot Inner 6
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> inventorySlotInner6;

    // Menu button to quit
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> quitButton;

    // Menu quit button text 
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> quitButtonText;

    // Menu background border
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UBorder> menuBorder;
};
