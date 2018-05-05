#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NPCAnimInstance.generated.h"

USTRUCT(BlueprintType)
struct FAnimCondition
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString conditionName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool conditionBool;

	FAnimCondition() {
		conditionName = "";
		conditionBool = false;
	}

	FAnimCondition(FString name) {
		conditionName = name;
		conditionBool = false;
	}
};


class ANPC;
UCLASS(transient, Blueprintable, hideCategories = AnimInstance, BlueprintType)
class PHOTO_API UNPCAnimInstance : public UAnimInstance
{
	GENERATED_UCLASS_BODY()

private:
	FVector actorVelocity;
	FRotator lookAtPlayerRot;
	ANPC* animatedNPC;

public:
	void SetAnimatedNPC(ANPC* npcSetTo);

	UFUNCTION(BlueprintPure)
		ANPC* GetAnimatedNPC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Condition")
		float animationSpeed = 1.0f;

	UFUNCTION(BlueprintCallable)
		void FreezeAnimations();

	UFUNCTION(BlueprintCallable)
		void UnfreezeAnimations();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Condition")
		TArray<FAnimCondition> animConditions;

	UFUNCTION(BlueprintCallable, Category = "Animation Condition")
		void AddAnimCondition(FString condition);

	UFUNCTION(BlueprintPure, Category = "Animation Condition")
		bool GetAnimCondition(FString condition);

	UFUNCTION(BlueprintCallable, Category = "Animation Condition")
		void SetAnimCondition(FString condition, bool conditionInput);

	void UpdateActorVelocity(FVector newVelocity);

	UFUNCTION(BlueprintPure)
		FVector GetActorVelocity();

	void UpdateLookAtPlayerRotation(FRotator newRotator);

	UFUNCTION(BlueprintPure)
		FRotator GetLookAtPlayerRotation();
};
