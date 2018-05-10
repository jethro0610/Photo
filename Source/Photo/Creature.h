// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "StatusConditionManager.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Creature.generated.h"

UCLASS()
class PHOTO_API ACreature : public APawn
{
	GENERATED_BODY()

public:
	ACreature();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UStatusConditionManager* conditionManager;
};
