// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerMovementComponent.h"
#include "Engine.h"

// Sets default values for this component's properties
UPlayerMovementComponent::UPlayerMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UPlayerMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!parentPlayer->IsOnGround(150.0f)) {
		velocity.Z -= gravitySpeed;
	}
	else {
		velocity.Z = 0.0f;
	}

	velocity += (parentPlayer->GetActorForwardVector() * (parentPlayer->yInputAxis* acceleration));
	velocity += (parentPlayer->GetActorRightVector() * (parentPlayer->xInputAxis* acceleration));
	velocity -= (FVector(velocity.X, velocity.Y, 0.0f) / deceleration);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(moveYAxis));

	ApplyMovementSliding(velocity);
}

void UPlayerMovementComponent::ApplyMovementSliding(FVector desiredVector) {
	FHitResult movementHit;

	parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + FVector::VectorPlaneProject(desiredVector,parentPlayer->GetGroundNormal(150.0f)), true, &movementHit);

	if (movementHit.IsValidBlockingHit()) {
		FVector slideNormal = FVector::VectorPlaneProject(desiredVector, movementHit.Normal);
		parentPlayer->SetActorLocation(parentPlayer->GetActorLocation() + slideNormal, true, &movementHit);
	}
}