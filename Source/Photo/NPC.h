#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "VelocityMovementComponent.h"
#include "NPCAnimInstance.h"
#include "Hitbox.h"
#include "NPC.generated.h"

UCLASS()
class PHOTO_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:	
	ANPC();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* collisionCapsule;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* model;

	UPROPERTY(EditAnywhere)
		UVelocityMovementComponent* movementComponent;

	UNPCAnimInstance* animationInstance;

	UPROPERTY(EditAnywhere)
		float awarenessDistance;

	UPROPERTY(EditAnywhere)
		float flashTime = 120.0f;

	UPROPERTY(EditAnywhere)
		bool canFlashByDefault = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float maxHealth = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString npcName = "NPC";

private:
	float deltaTick;
	TArray<UHitbox*> hitboxes;
	bool movementEnabled = true;
	bool canFlash;
	bool isFlashed;
	float flashTimer;
	float health;

public:
	FVector GetPlayerLocation();
	FRotator GetLookAtPlayerRotation();
	float GetDistanceFromPlayer();
	bool IsNoticingPlayer();
	bool PlayerIsLevel(float maxDifference);
	float GetDeltaTick();
	UHitbox* GetHitboxFromName(FName name);
	void EnableHitbox(UHitbox* hitboxToToggle);
	void DisableHitbox(UHitbox* hitboxToToggle);
	bool Flash();
	bool IsFlashed();

	bool ShouldMove();

	UFUNCTION(BlueprintCallable)
		void EnableHitboxFromName(FName name);

	UFUNCTION(BlueprintCallable)
		void DisableHitboxFromName(FName name);

	UFUNCTION(BlueprintCallable)
		void EnableMovement();

	UFUNCTION(BlueprintCallable)
		void DisableMovement();

	UFUNCTION(BlueprintCallable)
		void SetCanFlash(bool inputBool);

	UFUNCTION(BlueprintPure)
		float GetHealth();
};
