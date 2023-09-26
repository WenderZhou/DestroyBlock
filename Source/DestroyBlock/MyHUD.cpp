// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "CrosshairWidget.h"
#include "ScoreBoardWidget.h"
#include "SplitScreenDisplayWidget.h"
#include "Launcher.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"

AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CrosshairWidgetBP(TEXT("'/Game/Blueprints/BP_CrosshairWidget.BP_CrosshairWidget_C'"));
	if (CrosshairWidgetBP.Succeeded())
	{
		CrosshairWidgetClass = CrosshairWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> ScoreBoardWidgetBP(TEXT("'/Game/Blueprints/BP_ScoreBoardWidget.BP_ScoreBoardWidget_C'"));
	if (ScoreBoardWidgetBP.Succeeded())
	{
		ScoreBoardWidgetClass = ScoreBoardWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> SplitScreenDisplayWidgetBP(TEXT("'/Game/Blueprints/BP_SplitScreenDisplayWidget.BP_SplitScreenDisplayWidget_C'"));
	if (SplitScreenDisplayWidgetBP.Succeeded())
	{
		SplitScreenDisplayWidgetClass = SplitScreenDisplayWidgetBP.Class;
	}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	// Crosshair
	if (CrosshairWidget)
	{
		CrosshairWidget->Update(Player->MouseOffset, 1.0f - Player->CoolDownTimeRemain / Player->CoolDownTimeTotal);
	}

	// Score
	if (ScoreBoardWidget)
	{
		ScoreBoardWidget->UpdatePlayerScore(Player->Score);
		ScoreBoardWidget->UpdateNPCScore(NPC->Score);
	}
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SplitScreenDisplayWidgetClass)
	{
		SplitScreenDisplayWidget = CreateWidget<USplitScreenDisplayWidget>(GetWorld(), SplitScreenDisplayWidgetClass);
		if (SplitScreenDisplayWidget)
		{
			SplitScreenDisplayWidget->AddToViewport();
		}
	}

	if (ScoreBoardWidgetClass)
	{
		ScoreBoardWidget = CreateWidget<UScoreBoardWidget>(GetWorld(), ScoreBoardWidgetClass);
		if (ScoreBoardWidget)
		{
			ScoreBoardWidget->AddToViewport();
		}
	}

	if (CrosshairWidgetClass)
	{
		CrosshairWidget = CreateWidget<UCrosshairWidget>(GetWorld(), CrosshairWidgetClass);
		if (CrosshairWidget)
		{
			CrosshairWidget->AddToViewport();
		}
	}

	Player = Cast<ALauncher>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	NPC = Cast<ANPC>(UGameplayStatics::GetActorOfClass(GetWorld(), ANPC::StaticClass()));
}
