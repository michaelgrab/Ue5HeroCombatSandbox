// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpActor.h"

// Sets default values
AJumpActor::AJumpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	JumpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("JumpMesh"));
	JumpMesh->SetMobility(EComponentMobility::Movable);
	RootComponent = JumpMesh;
}

// Called when the game starts or when spawned
void AJumpActor::BeginPlay()
{
	Super::BeginPlay();
	m_startPos = GetActorLocation();

}

// Called every frame
void AJumpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_currentOffset += m_currentDirection * JumpSpeed * DeltaTime;

	if(m_currentDirection > 0 && m_currentOffset >= JumpHeight) {
		m_currentDirection = -1.0f;
		m_currentOffset = JumpHeight; // clamp to max height
	}
	else if(m_currentDirection < 0 && m_currentOffset <= 0.0f) {
		m_currentDirection = 1.0f;
		m_currentOffset = 0.0f; // clamp to min height
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, FString::Printf(TEXT("Offset: %f"), m_currentOffset));
	FVector newPosition = m_startPos;
	newPosition.Z += m_currentOffset;
	SetActorLocation(newPosition);
}

