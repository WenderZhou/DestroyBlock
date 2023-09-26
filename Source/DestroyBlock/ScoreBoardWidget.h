// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreBoardWidget.generated.h"

/**
 * 
 */
UCLASS()
class DESTROYBLOCK_API UScoreBoardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerScore;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NPCScore;

	void UpdatePlayerScore(int Score);

	void UpdateNPCScore(int Score);
};
