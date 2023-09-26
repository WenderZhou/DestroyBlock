// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Curves/CurveVector.h"
#include "Components/TimelineComponent.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	// Camera
	if (!CameraComponent)
	{
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		check(CameraComponent != nullptr);

		CameraComponent->SetupAttachment(RootComponent);

		CameraComponent->SetRelativeLocation(FVector(-150.0f, 0.0f, 250.0f));
	}

	// Mesh
	{
		MountPivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Cannon"));
		MountPivotComponent->SetupAttachment(RootComponent);

		MountMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mount"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/CannonMount.CannonMount'"));
		if (Mesh.Succeeded())
		{
			MountMeshComponent->SetStaticMesh(Mesh.Object);
		}

		MountMeshComponent->SetupAttachment(MountPivotComponent);
	}

	{
		BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Barrel"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/CannonBarrel.CannonBarrel'"));
		if (Mesh.Succeeded())
		{
			BarrelMeshComponent->SetStaticMesh(Mesh.Object);
		}
		BarrelMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 96.5f));
		BarrelMeshComponent->SetupAttachment(MountMeshComponent);
	}

	// Bullet Spawn Point
	{
		ProjectileSpawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSpawnPoint"));

		ProjectileSpawnPointComponent->SetupAttachment(BarrelMeshComponent);
	}

	{
		static ConstructorHelpers::FObjectFinder<UCurveVector> Curve(TEXT("'/Game/Curves/C_Cannon.C_Cannon'"));
		check(Curve.Succeeded());
		CurveVector = Curve.Object;

		TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));

		FOnTimelineVector InterpFunc;
		InterpFunc.BindUFunction(this, FName("Recoil"));
		TimelineComponent->AddInterpVector(CurveVector, InterpFunc);
	}

	Score = 0;
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPC::Fire()
{
	UClass* ProjectileClass = LoadObject<UClass>(nullptr, TEXT("'/Game/Blueprints/BP_Projectile.BP_Projectile_C'"));

	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPointComponent->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPointComponent->GetComponentRotation();

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AProjectile* Projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
			if (Projectile)
			{
				FVector LaunchDirection = SpawnRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);

				TimelineComponent->PlayFromStart();
			}
		}
	}
}

void ANPC::GainScore(int value)
{
	Score += value;
}

void ANPC::Recoil(FVector value)
{
	MountMeshComponent->SetRelativeLocation(value);
}