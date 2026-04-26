#include "EnemyCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
    PawnSensingComp->SightRadius = 2000.0f;
    PawnSensingComp->SetPeripheralVisionAngle(45.0f);

	AIControllerClass = AAIController::StaticClass();
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (PawnSensingComp)
    {
        PawnSensingComp->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
    }
}

void AEnemyCharacter::OnSeePawn(APawn* SeenPawn)
{
    if (SeenPawn->ActorHasTag(FName("Player")))
    {
        AAIController* AIC = Cast<AAIController>(GetController());
        if (AIC)
        {
            AIC->MoveToActor(SeenPawn, 50.0f); 

            float Distance = FVector::Dist(GetActorLocation(), SeenPawn->GetActorLocation());
            if (Distance < 150.0f)
            {
                PerformAttack();
            }
        }
    }
}

void AEnemyCharacter::PerformAttack()
{
    if (AttackMontage && !GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy NPC is performing an attack!"));
        PlayAnimMontage(AttackMontage);
    }
}