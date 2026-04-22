// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JumpActor.generated.h"

UCLASS()
class QA_TECH_TEST_API AJumpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* JumpMesh;

	// Jump settings
	UPROPERTY(EditAnywhere, Category = "JumpSettings")
	float JumpHeight = 200.0f;
	float JumpSpeed = 50.0f;

private:
	// position where actor was spawned
	FVector m_startPos;
	// current offset from start position, used for jump calculation
	float m_currentOffset = 0.0f;
	float m_currentDirection = 1.0f; // 1 for up, -1 for down

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
