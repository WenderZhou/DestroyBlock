// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplitScreenDisplayWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTROYBLOCK_API USplitScreenDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UImage* PlayerImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* NPCImage;
};
