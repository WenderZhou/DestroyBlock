// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Engine/Engine.h"

// Sets default values
ABlock::ABlock() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	if (!StaticMeshComponent)
	{
		StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
		StaticMeshComponent->SetSimulatePhysics(true);
		StaticMeshComponent->SetEnableGravity(true);
		StaticMeshComponent->SetupAttachment(RootComponent);
	}

	if (!TargetPointComponent)
	{
		TargetPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TargetComponent"));
		TargetPointComponent->SetupAttachment(StaticMeshComponent);
	}
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

