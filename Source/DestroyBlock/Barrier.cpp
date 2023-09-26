// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrier.h"

#include "Components/TimelineComponent.h"
#include "UObject/ConstructorHelpers.h"


// Sets default values
ABarrier::ABarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	{
		BarrierComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Barrier"));
		BarrierComponent->SetupAttachment(RootComponent);
	}

	// Mesh component 1
	{
		StaticMeshComponent1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Support"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/Barrier_1.Barrier_1'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent1->SetStaticMesh(Mesh.Object);
		}

		StaticMeshComponent1->SetupAttachment(BarrierComponent);
	}

	// Mesh component 2
	{
		StaticMeshComponent2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plate"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/Barrier_2.Barrier_2'"));
		if (Mesh.Succeeded())
		{
			StaticMeshComponent2->SetStaticMesh(Mesh.Object);
		}

		StaticMeshComponent2->SetupAttachment(BarrierComponent);
	}

	// Timeline Component
	{
		static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("'/Game/Curves/C_Barrier.C_Barrier'"));
		check(Curve.Succeeded());

		FloatCurve = Curve.Object;

		TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

		FOnTimelineFloat InterpFunc;
		InterpFunc.BindUFunction(this, FName("TimelineUpdate"));
		TimelineComponent->AddInterpFloat(FloatCurve, InterpFunc);

		//TimelineComponent->SetLooping(true);
	}

	{
		StartPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StartComponent"));
		StartPoint->SetupAttachment(RootComponent);

		EndPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EndComponent"));
		EndPoint->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void ABarrier::BeginPlay()
{
	Super::BeginPlay();
	
	TimelineComponent->PlayFromStart();
}

// Called every frame
void ABarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrier::TimelineUpdate(float value)
{
	FVector StartLocation = StartPoint->GetComponentLocation();
	FVector EndLocation = EndPoint->GetComponentLocation();

	FVector Location = FMath::Lerp(StartLocation, EndLocation, value);
	BarrierComponent->SetWorldLocation(Location);
}

