// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterPawn.h"

// Sets default values
AMyCharacterPawn::AMyCharacterPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create components
	CameraMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraMesh"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	
	//RootComponent = CameraMesh;
	Camera->SetupAttachment(CameraMesh);

	Camera->FieldOfView = 120.f;
	Camera->SetRelativeLocation(FVector(-200.0f, 0.0f, 150.0f));
}

void AMyCharacterPawn::MoveLR(float movementDelta) {
	FVector newLocation = GetActorLocation();
	newLocation.Y += movementDelta * MovementSpeed;
	SetActorLocation(newLocation);
}

// Called when the game starts or when spawned
void AMyCharacterPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Register for LR Movement
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMyCharacterPawn::MoveLR);
}

