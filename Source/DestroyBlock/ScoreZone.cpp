// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreZone.h"
#include "Launcher.h"
#include "NPC.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AScoreZone::AScoreZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (!BoxComponent)
	{
		BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
		RootComponent = BoxComponent;
	}
}

// Called when the game starts or when spawned
void AScoreZone::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AScoreZone::OnBeginOverlap);
}

// Called every frame
void AScoreZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreZone::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(FName(TEXT("PlayerBlock"))))
	{
		ALauncher* Launcher = Cast<ALauncher>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		Launcher->GainScore(1);
		OtherActor->SetLifeSpan(1.0f);
	}
	else if (OtherActor->ActorHasTag(FName(TEXT("NPCBlock"))))
	{
		ANPC* NPC = Cast<ANPC>(UGameplayStatics::GetActorOfClass(GetWorld(), ANPC::StaticClass()));
		NPC->GainScore(1);
		OtherActor->SetLifeSpan(1.0f);
	}
}



