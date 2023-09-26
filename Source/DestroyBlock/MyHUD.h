// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Launcher.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class DESTROYBLOCK_API AMyHUD : public AHUD
{
	GENERATED_BODY()

protected:
	/*UPROPERTY(EditDefaultsOnly)
	UTexture2D* CrosshairTexture;*/

public:
	AMyHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	// Crosshair
	UPROPERTY()
	class UCrosshairWidget* CrosshairWidget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUserWidget> CrosshairWidgetClass;

	// Score Board
	UPROPERTY()
	class UScoreBoardWidget* ScoreBoardWidget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUserWidget> ScoreBoardWidgetClass;

	// Split Screen Display
	UPROPERTY()
	class USplitScreenDisplayWidget* SplitScreenDisplayWidget;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UUserWidget> SplitScreenDisplayWidgetClass;

	UPROPERTY()
	class ALauncher* Player;

	UPROPERTY()
	class ANPC* NPC;
};
