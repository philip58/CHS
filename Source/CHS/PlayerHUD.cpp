// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerHUD.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/Color.h"

// Constructor
void UPlayerHUD::NativeConstruct()
{
    Super::NativeConstruct();

    if (quitButton)
    {
        FScriptDelegate scriptDelegate;
        scriptDelegate.BindUFunction(this, TEXT("Quit"));
        quitButton->OnClicked.Add(scriptDelegate);
    }
}

// Set interact pop up text to input 
void UPlayerHUD::SetInteractPopupText(const FString& text)
{
    if (interactPopupText)
    {
        interactPopupText->SetText(FText::FromString(text));
    }
}

// Set given inventory slot image to inputted image
void UPlayerHUD::SetHUDImage(UImage* currImage, UTexture2D* newImage, const float& opacity)
{
    if (currImage)
    {
        currImage->SetBrushFromTexture(newImage);
        currImage->SetOpacity(opacity);
    }
}

// Set the opacity for the HUD widget
void UPlayerHUD::SetHUDOpacity(UImage* currImage, const float& opacity)
{
    if (currImage)
    {
        currImage->SetOpacity(opacity);
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

// Quit on quit button click
void UPlayerHUD::Quit()
{
    UKismetSystemLibrary::QuitGame(
        this,
        GetOwningPlayer(),
        EQuitPreference::Quit,
        false
    );
}