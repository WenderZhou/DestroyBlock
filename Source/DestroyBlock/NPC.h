// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"
#include "NPC.generated.h"

UCLASS()
class DESTROYBLOCK_API ANPC : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ANPC();

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
	void GainScore(int value);

	UFUNCTION()
	void Recoil(FVector value);

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* MountPivotComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BarrelMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MountMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileSpawnPointComponent;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* TimelineComponent;

	UPROPERTY(VisibleAnywhere)
	class UCurveVector* CurveVector;

	UPROPERTY(VisibleAnywhere)
	int Score;
};
