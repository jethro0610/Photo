#include "SnapshotComponent.h"
#include "Engine.h"

USnapshotComponent::USnapshotComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USnapshotComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USnapshotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USnapshotComponent::TakeSnapshot() {
	FScreenshotRequest::RequestScreenshot(false);
}