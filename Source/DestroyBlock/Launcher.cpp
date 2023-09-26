// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

#include "Curves/CurveVector.h"
#include "Components/TimelineComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ALauncher::ALauncher()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}

	// Camera
	{
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		check(CameraComponent != nullptr);

		CameraComponent->SetupAttachment(RootComponent);

		CameraComponent->SetRelativeLocation(FVector(-150.0f, 0.0f, 250.0f));

		CameraComponent->bUsePawnControlRotation = true;
	}

	// Mount
	{
		MountPivotComponent = CreateDefaultSubobject<USceneComponent>(TEXT("MountPivot"));
		MountPivotComponent->SetupAttachment(RootComponent);

		MountMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MountMesh"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Meshes/CannonMount.CannonMount'"));
		if (Mesh.Succeeded())
		{
			MountMeshComponent->SetStaticMesh(Mesh.Object);
		}

		MountMeshComponent->SetupAttachment(MountPivotComponent);
	}

	// Barrel
	{
		BarrelMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelMesh"));
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

	CoolDownTimeRemain = 0.0f;
	CoolDownTimeTotal = 3.0f;
}

// Called when the game starts or when spawned
void ALauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CoolDownTimeRemain > 0.0f)
	{
		CoolDownTimeRemain -= DeltaTime;

		CoolDownTimeRemain = UKismetMathLibrary::FMax(CoolDownTimeRemain, 0);
	}
}

// Called to bind functionality to input
void ALauncher::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MouseMoveX", this, &ALauncher::MouseMoveX);
	PlayerInputComponent->BindAxis("MouseMoveY", this, &ALauncher::MouseMoveY);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ALauncher::Fire);
}

void ALauncher::MouseMoveX(float value)
{
	MouseOffset.X += value * 4.0f;

	float ViewportX = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().X;

	MouseOffset.X = UKismetMathLibrary::FMax(MouseOffset.X, -ViewportX * 0.25f);
	MouseOffset.X = UKismetMathLibrary::FMin(MouseOffset.X, ViewportX * 0.25f);

	UpdateCannonDirection();
}

void ALauncher::MouseMoveY(float value)
{
	MouseOffset.Y += value * 4.0f;

	float ViewportY = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().Y * 0.5f;

	MouseOffset.Y = UKismetMathLibrary::FMax(MouseOffset.Y, -ViewportY);
	MouseOffset.Y = UKismetMathLibrary::FMin(MouseOffset.Y, ViewportY);

	UpdateCannonDirection();
}

void ALauncher::Fire()
{
	if (CoolDownTimeRemain > 0.0f)
		return;

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

				CoolDownTimeRemain = CoolDownTimeTotal;

				TimelineComponent->PlayFromStart();
			}
		}
	}
}

void ALauncher::UpdateCannonDirection()
{
	FVector CameraLocation = CameraComponent->GetComponentLocation();
	FRotator CameraRotator = CameraComponent->GetComponentRotation();

	FVector CameraForwardVector = UKismetMathLibrary::GetForwardVector(CameraRotator);
	FVector CameraRightVector = UKismetMathLibrary::GetRightVector(CameraRotator);
	FVector CameraUpVector = UKismetMathLibrary::GetUpVector(CameraRotator);

	float ViewportZ = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().X * 0.25f;

	FVector CameraDirection = CameraForwardVector * ViewportZ + CameraRightVector * MouseOffset.X - CameraUpVector * MouseOffset.Y;
	CameraDirection.Normalize();

	FVector TargetLocation = CameraLocation + CameraDirection * TargetDistance;
	FVector BarrelLocation = BarrelMeshComponent->GetComponentLocation();

	FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(BarrelLocation, TargetLocation);
	
	BarrelMeshComponent->SetRelativeRotation(FRotator(NewRotator.Pitch, 0.f, 0.f));
	MountPivotComponent->SetRelativeRotation(FRotator(0.f, NewRotator.Yaw, 0.f));
}

void ALauncher::GainScore(int value)
{
	Score += value;
}

void ALauncher::Recoil(FVector value)
{
	MountMeshComponent->SetRelativeLocation(value);
}