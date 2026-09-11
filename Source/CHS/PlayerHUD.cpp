// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/TextBlock.h"
#include "PlayerHUD.h"

void UPlayerHUD::SetInteractPopupText(const FString& text)
{
    if (interactPopupText)
    {
        interactPopupText->SetText(FText::FromString(text));
    }
}

