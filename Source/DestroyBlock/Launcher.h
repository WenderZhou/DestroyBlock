// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"
#include "Launcher.generated.h"

UCLASS()
class DESTROYBLOCK_API ALauncher : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void UpdateCannonDirection();

	UFUNCTION()
	void GainScore(int value);

	UFUNCTION()
	void Recoil(FVector value);

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* MountPivotComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MountMeshComponent;

	/*UPROPERTY(VisibleAnywhere)
	USceneComponent* BarrelPivotComponent;*/

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BarrelMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPointComponent;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* TimelineComponent;

	UPROPERTY(VisibleAnywhere)
	class UCurveVector* CurveVector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D MouseOffset;

	UPROPERTY(EditAnywhere)
	float TargetDistance;

	UPROPERTY(VisibleAnywhere)
	int Score;

	UPROPERTY(VisibleAnywhere)
	float CoolDownTimeRemain;

	UPROPERTY(VisibleAnywhere)
	float CoolDownTimeTotal;
};
