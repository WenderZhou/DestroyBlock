// Fill out your copyright notice in the Description page of Project Settings.


#include "CrosshairWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"

void UCrosshairWidget::Update(FVector2D MouseOffset, float CoolDownPercent)
{
	Cast<UCanvasPanelSlot>(CrosshairImage->Slot)->SetPosition(MouseOffset);

	if (CoolDownPercent < 1.0f)
	{
		CoolDownProgressBar->SetVisibility(ESlateVisibility::Visible);
		Cast<UCanvasPanelSlot>(CoolDownProgressBar->Slot)->SetPosition(MouseOffset);
		CoolDownProgressBar->SetPercent(CoolDownPercent);
	}
	else
	{
		CoolDownProgressBar->SetVisibility(ESlateVisibility::Hidden);
	}
}