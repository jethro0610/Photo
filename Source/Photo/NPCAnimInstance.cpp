#include "NPCAnimInstance.h"
#include "NPC.h"

UNPCAnimInstance::UNPCAnimInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void UNPCAnimInstance::SetAnimatedNPC(ANPC* npcSetTo) {
	animatedNPC = npcSetTo;
}

ANPC* UNPCAnimInstance::GetAnimatedNPC() {
	return animatedNPC;
}

void UNPCAnimInstance::FreezeAnimations() {
	animationSpeed = 0.0f;
}

void UNPCAnimInstance::UnfreezeAnimations() {
	animationSpeed = 1.0f;
}

void UNPCAnimInstance::AddAnimCondition(FString conditionName) {
	animConditions.Add(FAnimCondition(conditionName));
}

bool UNPCAnimInstance::GetAnimCondition(FString condition) {
	bool returnBool = false;
	for (int i = 0; i < animConditions.Num(); i++) {
		if (animConditions[i].conditionName == condition)
			returnBool = animConditions[i].conditionBool;
	}
	return returnBool;
}

void UNPCAnimInstance::SetAnimCondition(FString condition, bool conditionInput) {
	for (int i = 0; i < animConditions.Num(); i++) {
		if (animConditions[i].conditionName == condition)
			animConditions[i].conditionBool = conditionInput;
	}
}

void UNPCAnimInstance::UpdateActorVelocity(FVector newVelocity) {
	actorVelocity = newVelocity;
}

FVector UNPCAnimInstance::GetActorVelocity() {
	return actorVelocity;
}

void UNPCAnimInstance::UpdateLookAtPlayerRotation(FRotator newRotator) {
	lookAtPlayerRot = newRotator;
}

FRotator UNPCAnimInstance::GetLookAtPlayerRotation() {
	return lookAtPlayerRot;
}