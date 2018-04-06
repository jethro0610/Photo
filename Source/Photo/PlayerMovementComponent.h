// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhotoPlayer.h"
#include "PlayerMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PHOTO_API UPlayerMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	APhotoPlayer* parentPlayer;
	
	float moveXAxis;
	float moveYAxis;

	FVector velocity;
	
	UPROPERTY(EditAnywhere)
		float gravitySpeed;

	UPROPERTY(EditAnywhere)
		float acceleration;

	UPROPERTY(EditAnywhere)
		float deceleration;

	FVector GetRelativeVector(FVector inputVector);
	void ApplyMovement(FVector desiredMovement);
};
