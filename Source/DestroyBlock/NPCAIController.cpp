// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "behaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Launcher.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("'/Game/AI/BT_NPC.BT_NPC'"));
	if (Obj.Succeeded())
	{
		BehaviorTree = Obj.Object;
	}

	BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));

	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
}

void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComponent->StartTree(*BehaviorTree);
}

void ANPCAIController::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
	if (BlackboardComponent)
	{
		BlackboardComponent->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

UBlackboardComponent * ANPCAIController::GetBlackboard() const
{
	return BlackboardComponent;
}
