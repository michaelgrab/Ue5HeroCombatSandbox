// Fill out your copyright notice in the Description page of Project Settings.


#include "ANS_HandFastPunch.h"
#include "MyCharacter.h"

void UANS_HandFastPunch::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp && MeshComp->GetOwner())
	{
		if (AMyCharacter* Character = Cast<AMyCharacter>(MeshComp->GetOwner()))
		{
			Character->ClearHitList();
		}
	}
}

void UANS_HandFastPunch::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) {
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!MeshComp || !MeshComp->GetOwner()) return;
	AActor* Owner = MeshComp->GetOwner();
	UWorld* World = Owner->GetWorld();
	FName BoneName;
	switch (ActiveLimb)
	{
	case EAttackLimb::RightHand: BoneName = TEXT("hand_r"); break;
	case EAttackLimb::LeftHand:  BoneName = TEXT("hand_l"); break;
	case EAttackLimb::RightFoot: BoneName = TEXT("foot_r"); break;
	case EAttackLimb::LeftFoot:  BoneName = TEXT("foot_l"); break;
	default:                     BoneName = TEXT("hand_r"); break;
	}

	FVector BoneLocation = MeshComp->GetBoneLocation(BoneName, EBoneSpaces::WorldSpace);

	UE_LOG(LogTemp, Warning, TEXT("Bone '%s' location: '%s'"), *BoneName.ToString(), *BoneLocation.ToString());

	TArray<FHitResult> HitResults;

	if (World == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("World is null"));
		return;
	}
	DrawDebugSphere(World, BoneLocation, TraceRadius, 16, FColor::Red, false, 0.0f, 0, 2.0f);
	bool bHit = World->SweepMultiByChannel(
		HitResults,
		BoneLocation,
		BoneLocation,
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(TraceRadius)
	);
	if (bHit) {
		for (const FHitResult& Hit : HitResults) {
			AActor* HitActor = Hit.GetActor();
			if (HitActor) {
				UE_LOG(LogTemp, Warning, TEXT("Hit actor: %s"), *HitActor->GetActorLabel());
				//MyCharacter->RegisterHit(HitActor);
			}
		}
	}
}
