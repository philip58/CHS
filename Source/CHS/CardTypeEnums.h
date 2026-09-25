// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CardTypeEnums.generated.h"

UENUM(BlueprintType)
enum class ECardType : uint8
{
    CT_Club    UMETA(DisplayName = "Club"),
    CT_Spade   UMETA(DisplayName = "Spade"),
    CT_Heart   UMETA(DisplayName = "Heart"),
    CT_Diamond UMETA(DisplayName = "Diamond"),
    CT_Black   UMETA(DisplayName = "Black"),
    CT_Red     UMETA(DisplayName = "Red"),
    CT_Green   UMETA(DisplayName = "Green"),
    CT_Blue    UMETA(DisplayName = "Blue"),
    CT_Yellow  UMETA(DisplayName = "Yellow"),
    CT_Wild    UMETA(DisplayName = "Wild")
};

UENUM(BlueprintType)
enum class ECardValue : uint8
{
    CV_0        UMETA(DisplayName = "0"),
    CV_1        UMETA(DisplayName = "1"),
    CV_2        UMETA(DisplayName = "2"),
    CV_3        UMETA(DisplayName = "3"),
    CV_4        UMETA(DisplayName = "4"),
    CV_5        UMETA(DisplayName = "5"),
    CV_6        UMETA(DisplayName = "6"),
    CV_7        UMETA(DisplayName = "7"),
    CV_8        UMETA(DisplayName = "8"),
    CV_9        UMETA(DisplayName = "9"),
    CV_10       UMETA(DisplayName = "10"),
    CV_Jack     UMETA(DisplayName = "Jack"),
    CV_Queen    UMETA(DisplayName = "Queen"),
    CV_King     UMETA(DisplayName = "King"),
    CV_Ace      UMETA(DisplayName = "Ace"),
    CV_Joker    UMETA(DisplayName = "Joker"),
    CV_Reverse  UMETA(DisplayName = "Reverse"),
    CV_Skip     UMETA(DisplayName = "Skip"),
    CV_DrawTwo  UMETA(DisplayName = "DrawTwo"),
    CV_DrawFour UMETA(DisplayName = "DrawFour"),
    CV_Wild     UMETA(DisplayName = "Wild")
};


