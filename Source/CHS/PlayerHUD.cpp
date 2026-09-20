// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Math/Color.h"
#include "PlayerHUD.h"

// Set interact pop up text to input 
void UPlayerHUD::SetInteractPopupText(const FString& text)
{
    if (interactPopupText)
    {
        interactPopupText->SetText(FText::FromString(text));
    }
}

// Set given inventory slot image to inputted image
void UPlayerHUD::SetInventoryImage(UImage* currInventoryImage, UTexture2D* newInventoryImage, const float& opacity)
{
    if (currInventoryImage)
    {
        currInventoryImage->SetBrushFromTexture(newInventoryImage);
        currInventoryImage->SetOpacity(opacity);
    }
}

// Set the color of the inventory slot
void UPlayerHUD::SetInventorySlotColor(UBorder* inventorySlot, float rColor, float gColor, float bColor, float aColor)
{
    if (inventorySlot)
    {
        FLinearColor linearColor(rColor,gColor,bColor,aColor);
        inventorySlot->SetBrushColor(linearColor);
    }
    
}

