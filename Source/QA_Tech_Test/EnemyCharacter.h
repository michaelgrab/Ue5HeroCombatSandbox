#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;

UCLASS()
class QA_TECH_TEST_API AEnemyCharacter : public ABaseCharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, Category = "AI")
    UPawnSensingComponent* PawnSensingComp;

    UFUNCTION()
    void OnSeePawn(APawn* SeenPawn);

    void PerformAttack();

    UPROPERTY(EditAnywhere, Category = "AI")
    UAnimMontage* AttackMontage;

    FTimerHandle AttackTimerHandle;
};