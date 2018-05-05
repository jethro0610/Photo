#include "NPC.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	collisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	collisionCapsule->SetCollisionProfileName("BlockAll");
	RootComponent = collisionCapsule;

	model = CreateDefaultSubobject<USkeletalMeshComponent>("Model");
	model->AttachTo(RootComponent);

	movementComponent = CreateDefaultSubobject<UVelocityMovementComponent>("Movement Component");
	movementComponent->gravitySpeed = 0.25f;
	movementComponent->friction = 0.2f;
	movementComponent->maxWalkSpeed = 8.0f;
}

void ANPC::BeginPlay()
{
	Super::BeginPlay();

	animationInstance = Cast<UNPCAnimInstance>(model->GetAnimInstance());
	animationInstance->SetAnimatedNPC(this);

	TArray<USceneComponent*> hitboxComponents = model->GetAttachChildren();
	for (int i = 0; i < hitboxComponents.Num(); i++) {
		if (hitboxComponents[i]->IsA(UHitbox::StaticClass()))
			hitboxes.Add(Cast<UHitbox, USceneComponent>(hitboxComponents[i]));
	}

	if (canFlashByDefault == true) {
		canFlash = true;
	}
	else {
		canFlash = false;
	}

	health = maxHealth;
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	deltaTick = DeltaTime * 60.0f;

	animationInstance->UpdateActorVelocity(movementComponent->GetVelocity());
	animationInstance->UpdateLookAtPlayerRotation(GetLookAtPlayerRotation());

	if (isFlashed == true) {
		flashTimer -= deltaTick;
		movementComponent->SetVelocity(FVector::ZeroVector);
		animationInstance->FreezeAnimations();
	}

	if (flashTimer <= 0.0f) {
		isFlashed = false;
		animationInstance->UnfreezeAnimations();
		if (canFlashByDefault == true) {
			canFlash = true;
		}
	}
}

float ANPC::GetDeltaTick() {
	return deltaTick;
}

FRotator ANPC::GetLookAtPlayerRotation() {
	return UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetPlayerLocation()) - FRotator(0.0f, 90.0f, 0.0f);
}

FVector ANPC::GetPlayerLocation() {
	return GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}

float ANPC::GetDistanceFromPlayer() {
	return FVector::Dist(GetActorLocation(), GetPlayerLocation());
}

bool ANPC::IsNoticingPlayer() {
	if (GetDistanceFromPlayer() <= awarenessDistance) {
		return true;
	}
	else {
		return false;
	}
}

bool ANPC::PlayerIsLevel(float maxDistance) {
	float zDistance = FMath::Abs(GetPlayerLocation().Z - GetActorLocation().Z);
	if (zDistance <= maxDistance) {
		return true;
	}
	else {
		return false;
	}
}

UHitbox* ANPC::GetHitboxFromName(FName name) {
	UHitbox* returnHitbox = nullptr;
	
	for (int i = 0; i < hitboxes.Num(); i++) {
		if (hitboxes[i]->hitboxName == name) {
			returnHitbox = hitboxes[i];
		}
	}
	return returnHitbox;
}

void ANPC::EnableHitbox(UHitbox* hitboxToToggle) {
	if(hitboxToToggle->appliedHit == false)
		hitboxToToggle->isHitting = true;
}

void ANPC::DisableHitbox(UHitbox* hitboxToToggle) {
	hitboxToToggle->isHitting = false;
	hitboxToToggle->appliedHit = false;
}

void ANPC::EnableHitboxFromName(FName name) {
	EnableHitbox(GetHitboxFromName(name));
}

void ANPC::DisableHitboxFromName(FName name) {
	DisableHitbox(GetHitboxFromName(name));
}

void ANPC::EnableMovement() {
	movementEnabled = true;
}

void ANPC::DisableMovement() {
	movementEnabled = false;
}

bool ANPC::ShouldMove() {
	if (isFlashed == true) {
		return false;
	}
	else {
		return movementEnabled;
	}
}

void ANPC::SetCanFlash(bool inputBool) {
	canFlash = inputBool;
}

bool ANPC::IsFlashed() {
	return isFlashed;
}

bool ANPC::Flash() {
	if (canFlash == true) {
		isFlashed = true;
		flashTimer = flashTime;
		canFlash = false;
		if(npcName == "Golem")
			health -= 75.0f;

		if (health <= 0.0f)
			Destroy();

		return true;
	}
	else {
		return false;
	}
}

float ANPC::GetHealth() {
	return health;
}