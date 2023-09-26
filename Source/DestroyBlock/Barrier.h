// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Barrier.generated.h"

UCLASS()
class DESTROYBLOCK_API ABarrier : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrier();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BarrierComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent1;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent2;

	UPROPERTY(VisibleAnywhere)
	class UTimelineComponent* TimelineComponent;

	UPROPERTY(VisibleAnywhere)
	UCurveFloat* FloatCurve;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* StartPoint;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* EndPoint;

	UFUNCTION()
	void TimelineUpdate(float value);
};
