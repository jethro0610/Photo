#include "Creature.h"
ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;

	conditionManager = CreateDefaultSubobject<UStatusConditionManager>("Condition Manager");
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

