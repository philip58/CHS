// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "Components/Image.h"
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
void UPlayerHUD::SetInventoryImage(UImage* currInventoryImage, UImage* newInventoryImage, const float& opacity)
{
    if (currInventoryImage)
    {
        currInventoryImage = newInventoryImage;
        newInventoryImage->SetOpacity(opacity);
    }
}

