// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_HandFastPunch.generated.h"

UENUM(BlueprintType)
enum class EAttackLimb : uint8
{
    RightHand    UMETA(DisplayName = "Right Hand"),
    LeftHand     UMETA(DisplayName = "Left Hand"),
    RightFoot    UMETA(DisplayName = "Right Foot"),
    LeftFoot     UMETA(DisplayName = "Left Foot")
};

UCLASS()
class QA_TECH_TEST_API UANS_HandFastPunch : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
    
    virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
    
    UPROPERTY(EditAnywhere, Category = "Settings")
    EAttackLimb ActiveLimb;

    UPROPERTY(EditAnywhere, Category = "Settings")
    float TraceRadius = 50.0f;


};

