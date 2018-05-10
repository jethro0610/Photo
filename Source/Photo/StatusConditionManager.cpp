#include "StatusConditionManager.h"

UStatusConditionManager::UStatusConditionManager()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatusConditionManager::BeginPlay()
{
	Super::BeginPlay();

}

void UStatusConditionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatusConditionManager::SetBurning(bool isActive) {
	isBurning = isActive;
	if (isActive) {
		burnEnabled.Execute();
	}
	else {
		burnDisabled.Execute();
	}
}

void UStatusConditionManager::SetWet(bool isActive) {
	isWet = isActive;
	if (isActive) {
		wetEnabled.Execute();
	}
	else {
		wetDisabled.Execute();
	}
}

void UStatusConditionManager::SetSleeping(bool isActive) {
	isSleeping = isActive;
	if (isActive) {
		sleepEnabled.Execute();
	}
	else {
		sleepDisabled.Execute();
	}
}

void UStatusConditionManager::SetSmelling(bool isActive) {
	isSmelling = isActive;
	if (isActive) {
		smellEnabled.Execute();
	}
	else {
		smellDisabled.Execute();
	}
}

bool UStatusConditionManager::IsBurning() {
	return isBurning;
}

bool UStatusConditionManager::IsWet() {
	return isWet;
}

bool UStatusConditionManager::IsSleeping() {
	return isSleeping;
}

bool UStatusConditionManager::IsSmelling() {
	return isSmelling;
}