// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/behaviorTreeTypes.h"
#include "UObject/Uobjectglobals.h"
#include "NPCFindTarget.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DESTROYBLOCK_API UNPCFindTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY ()
	
public:
	UNPCFindTarget(FObjectInitializer const& ObjectInitializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory);
	
	virtual void TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds) override;
};
