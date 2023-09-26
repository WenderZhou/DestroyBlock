// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTROYBLOCK_API UCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* CrosshairImage;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* CoolDownProgressBar;

	void Update(FVector2D MouseOffset, float CoolDownPercent);
};
