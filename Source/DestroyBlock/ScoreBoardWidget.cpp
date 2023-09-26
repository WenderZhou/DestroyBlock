// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreBoardWidget.h"
#include "Components/TextBlock.h"

void UScoreBoardWidget::UpdatePlayerScore(int Score)
{
	FString TextString = "Score: " + FString::FromInt(Score);
	PlayerScore->SetText(FText::FromString(TextString));
}

void UScoreBoardWidget::UpdateNPCScore(int Score)
{
	FString TextString = "Score: " + FString::FromInt(Score);
	NPCScore->SetText(FText::FromString(TextString));
}