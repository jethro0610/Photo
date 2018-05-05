#include "Hitbox.h"

UHitbox::UHitbox()
{
	PrimaryComponentTick.bCanEverTick = true;

	collisionBubble = CreateDefaultSubobject<UCapsuleComponent>("Bubble");
	collisionBubble->AttachTo(this);
	collisionBubble->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	collisionBubble->bGenerateOverlapEvents = true;
}

void UHitbox::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHitbox::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

