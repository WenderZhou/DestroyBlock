// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCFindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NPCAIController.h"
#include "NPC.h"
#include "NPCBlackboardKeys.h"
#include "Block.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

UNPCFindTarget::UNPCFindTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Target");

	bNotifyTick = true;
}

EBTNodeResult::Type UNPCFindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComponent, uint8* NodeMemory)
{
	// Get AI controller and its NPC
	auto const AIController = Cast<ANPCAIController>(OwnerComponent.GetAIOwner());
	ANPC* NPC = Cast<ANPC>(AIController->GetPawn());

	FRotator StartRotation = NPC->BarrelMeshComponent->GetComponentRotation();
	AIController->GetBlackboard()->SetValueAsRotator(NPCBlackboardKeys::StartRotation, StartRotation);

	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("NPCBlock"), Targets);

	if (Targets.Num() > 0)
	{
		int TargetIndex = FMath::RandRange(0, Targets.Num() - 1);

		FVector TargetLocation = Cast<ABlock>(Targets[TargetIndex])->TargetPointComponent->GetComponentLocation();
		FVector BarrelLocation = NPC->BarrelMeshComponent->GetComponentLocation();

		FVector NewBarrelDirection = TargetLocation - BarrelLocation;

		FRotator TargetRotation = UKismetMathLibrary::MakeRotationFromAxes(NewBarrelDirection, FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 0.0f));
		AIController->GetBlackboard()->SetValueAsRotator(NPCBlackboardKeys::TargetRotation, TargetRotation);

		AIController->GetBlackboard()->SetValueAsFloat(NPCBlackboardKeys::Interpfactor, 0.0f);

		/*FString DebugMessage = FString::Printf(TEXT("Target Location is %f, %f, %f"), TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);*/

		// Finish with success
		return EBTNodeResult::InProgress;
	}
	else
	{
		FinishLatentTask(OwnerComponent, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
}

void UNPCFindTarget::TickTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	auto const AIController = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	ANPC* NPC = Cast<ANPC>(AIController->GetPawn());

	float InterpFactor = AIController->GetBlackboard()->GetValueAsFloat(NPCBlackboardKeys::Interpfactor) + DeltaSeconds;
	FRotator StartRotation = AIController->GetBlackboard()->GetValueAsRotator(NPCBlackboardKeys::StartRotation);
	FRotator TargetRotation = AIController->GetBlackboard()->GetValueAsRotator(NPCBlackboardKeys::TargetRotation);

	FRotator InterpRotation = FMath::Lerp(StartRotation, TargetRotation, InterpFactor);

	NPC->BarrelMeshComponent->SetRelativeRotation(FRotator(InterpRotation.Pitch, 0.f, 0.f));
	NPC->MountPivotComponent->SetRelativeRotation(FRotator(0.f, InterpRotation.Yaw, 0.f));

	if (InterpFactor > 1.0f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		AIController->GetBlackboard()->SetValueAsFloat(NPCBlackboardKeys::Interpfactor, InterpFactor);
	}
}