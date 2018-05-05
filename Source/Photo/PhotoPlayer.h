#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "VelocityMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SnapshotComponent.h"
#include "PhotoCameraComponent.h"
#include "PlayerUI.h"
#include "NPC.h"
#include "PhotoPlayer.generated.h"

UCLASS()
class PHOTO_API APhotoPlayer : public APawn
{
	GENERATED_BODY()

public:
	APhotoPlayer();

protected:
	virtual void BeginPlay() override;

private:
	float cameraPan;
	float cameraTilt;
	float xInputAxis;
	float yInputAxis;
	float health = 0.0f;
	float flashCooldown = 0.0f;
	float photoCooldown = 0.0f;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UCapsuleComponent* collisionCapsule;

	UPROPERTY(EditAnywhere)
		UCameraComponent* camera;

	UPROPERTY(EditAnywhere)
		USnapshotComponent* snapshotComponent;

	UPROPERTY(EditAnywhere)
		UPhotoCameraComponent* photoCameraComponent;

	UPROPERTY(EditAnywhere)
		UPlayerUI* playerUI;

	UPROPERTY(EditAnywhere)
		UVelocityMovementComponent* movementComponent;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* targetVisual;

	TArray<ANPC*> GetNPCsInView();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float flashCooldownTime = 120.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float photoCooldownTime = 60.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int photoXP = 0;

	UFUNCTION(BlueprintPure)
		float GetHealth();

	UFUNCTION(BlueprintPure)
		float GetFlashCooldown();

	UFUNCTION(BlueprintPure)
		float GetPhotoCooldown();

	void UpdateMouseX(float axisValue);
	void UpdateMouseY(float axisValue);

	void TestInputFunction();
	void Test2Function();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ANPC* targetNPC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ANPC* lockOnNPC;

	void UpdateInputX(float axisValue);
	void UpdateInputY(float axisValue);

	void JumpInput();
	void LockInput();
	void FlashInput();
	void PhotoInput();
	void ExportInput();

	void Flash();

	UFUNCTION()
	void OnOverlap(class UPrimitiveComponent* MainActor, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
