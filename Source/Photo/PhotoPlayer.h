// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "SnapshotComponent.h"
#include "PhotoCameraComponent.h"
#include "PhotoPlayer.generated.h"

UCLASS()
class PHOTO_API APhotoPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APhotoPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UBoxComponent* collisionBox;

	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		USnapshotComponent* snapshotComponent;

	UPROPERTY(EditAnywhere)
		UPhotoCameraComponent* photoCameraComponent;

	void UpdateMouseX(float axisValue);
	float cameraPan;

	void UpdateMouseY(float axisValue);
	float cameraTilt;

	void TestInputFunction();
	void Test2Function();
};
