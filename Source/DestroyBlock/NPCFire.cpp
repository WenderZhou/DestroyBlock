// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCFire.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NPCAIController.h"
#include "NPC.h"
#include "NPCBlackboardKeys.h"

UNPCFire::UNPCFire(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Fire");
}

EBTNodeResult::Type UNPCFire::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	// Get AI controller and its NPC
	auto const AIController = Cast<ANPCAIController>(OwnerComponent.GetAIOwner());
	ANPC* NPC = Cast<ANPC>(AIController->GetPawn());

	NPC->Fire();

	// Finish with success
	FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}