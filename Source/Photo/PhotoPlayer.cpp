#include "PhotoPlayer.h"
#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Hitbox.h"
#include "Components/InputComponent.h"

APhotoPlayer::APhotoPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	collisionCapsule = CreateDefaultSubobject<UCapsuleComponent>("Collider");
	collisionCapsule->SetCollisionProfileName("BlockAll");
	RootComponent = collisionCapsule;
	collisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &APhotoPlayer::OnOverlap);
	
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	camera->AttachTo(RootComponent);
	camera->SetRelativeLocation(FVector(0.0f, 0.0f, 32.0f));

	snapshotComponent = CreateDefaultSubobject<USnapshotComponent>("Snapshot Component");
	photoCameraComponent = CreateDefaultSubobject<UPhotoCameraComponent>("Photo Component");

	movementComponent = CreateDefaultSubobject<UVelocityMovementComponent>("Movement Component");
	movementComponent->gravitySpeed = 0.25f;
	movementComponent->friction = 0.2f;
	movementComponent->maxWalkSpeed = 8.0f;

	targetVisual = CreateDefaultSubobject<UStaticMeshComponent>("Targeter");
	targetVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APhotoPlayer::BeginPlay()
{
	Super::BeginPlay();

	cameraTilt = GetActorRotation().Pitch;
	cameraPan = GetActorRotation().Yaw;

	if (playerUI->IsValidLowLevel()) {
		playerUI->parentPlayer = this;
		playerUI->AddToViewport();
	}

	health = maxHealth;
	flashCooldown = flashCooldownTime;
	photoCooldown = photoCooldownTime;
}

void APhotoPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float deltaTick = DeltaTime * 60.0f;


	if(lockOnNPC->IsValidLowLevel()) {
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), lockOnNPC->GetActorLocation());
		targetRotation.Normalize();
		cameraPan = targetRotation.Yaw;
		cameraTilt = targetRotation.Pitch;
	}
	SetActorRotation(FRotator(0.0f, cameraPan, 0.0f));
	camera->SetRelativeRotation(FRotator(cameraTilt, 0.0f, 0.0f));

	photoCameraComponent->SetWorldLocation(camera->GetComponentLocation());
	photoCameraComponent->SetWorldRotation(camera->GetComponentRotation()); 

	if (movementComponent->IsOnGround()) {
		movementComponent->AddVelocity((GetActorForwardVector()*yInputAxis*movementComponent->acceleration*deltaTick));
		movementComponent->AddVelocity((GetActorRightVector()*xInputAxis*movementComponent->acceleration*deltaTick));
	}

	if (flashCooldown > flashCooldownTime) {
		flashCooldown = flashCooldownTime;
	}

	if (flashCooldown != flashCooldownTime) {
		flashCooldown += deltaTick;
	}

	if (photoCooldown > photoCooldownTime) {
		photoCooldown = photoCooldownTime;
	}

	if (photoCooldown != photoCooldownTime) {
		photoCooldown += deltaTick;
	}

	if (!lockOnNPC->IsValidLowLevel()) {
		targetNPC = nullptr;
		float targetDistance = -1.0f;
		for (int i = 0; i < GetNPCsInView().Num(); i++) {
			float currentDistance = FVector::Dist(GetActorLocation(), GetNPCsInView()[i]->GetActorLocation());
			if (currentDistance < targetDistance || targetDistance == -1.0f) {
				targetDistance = currentDistance;
				targetNPC = GetNPCsInView()[i];
			}
		}
	}

	if (targetNPC != nullptr) {
		targetVisual->SetVisibility(true);
		targetVisual->SetWorldLocation(targetNPC->GetActorLocation() + FVector(0.0f,0.0f,200.0f));
	}
	else {
		targetVisual->SetVisibility(false);
	}
}

void APhotoPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Mouse X", this, &APhotoPlayer::UpdateMouseX);
	PlayerInputComponent->BindAxis("Mouse Y", this, &APhotoPlayer::UpdateMouseY);
	PlayerInputComponent->BindAxis("Move X", this, &APhotoPlayer::UpdateInputX);
	PlayerInputComponent->BindAxis("Move Y", this, &APhotoPlayer::UpdateInputY);
	PlayerInputComponent->BindAction("Take Photo", EInputEvent::IE_Released, this, &APhotoPlayer::PhotoInput);
	PlayerInputComponent->BindAction("Export Photos", EInputEvent::IE_Released, this, &APhotoPlayer::ExportInput);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APhotoPlayer::JumpInput);
	PlayerInputComponent->BindAction("Lock", EInputEvent::IE_Released, this, &APhotoPlayer::LockInput);
	PlayerInputComponent->BindAction("Flash", EInputEvent::IE_Pressed, this, &APhotoPlayer::FlashInput);
}

void APhotoPlayer::UpdateMouseX(float axisValue) {
	if (!lockOnNPC->IsValidLowLevel()) {
		cameraPan += axisValue;
	}
}

void APhotoPlayer::UpdateMouseY(float axisValue) {
	if (!lockOnNPC->IsValidLowLevel()) {
		cameraTilt += axisValue;
		cameraTilt = FMath::Clamp(cameraTilt, -85.0f, 85.0f);
	}
}

void APhotoPlayer::UpdateInputX(float axisValue) {
	xInputAxis = axisValue;
}

void APhotoPlayer::UpdateInputY(float axisValue) {
	yInputAxis = axisValue;
}

void APhotoPlayer::PhotoInput() {
	photoCameraComponent->TakePhoto();
	photoCooldown = 0.0f;
	playerUI->ScreenBlink(FColor::Black);
	for (int i = 0; i < GetNPCsInView().Num(); i++) {
		if (GetNPCsInView()[i]->IsFlashed() && GetNPCsInView()[i]->npcName == "Golem") {
			photoXP += 1000;
		}
		else {
			if(GetNPCsInView()[i]->npcName != "Golem")
				photoXP += 250;
		}
	}
}

void APhotoPlayer::ExportInput() {
	photoCameraComponent->ExportPhotos();
}

void APhotoPlayer::Flash() {
	if (flashCooldown == flashCooldownTime) {
		bool flashedEnemy = false;
		flashCooldown = 0.0f;
		for (int i = 0; i < GetNPCsInView().Num(); i++) {
			if (GetNPCsInView()[i]->Flash()) {
				flashedEnemy = true;
			}
		}

		if (flashedEnemy == true) {
			playerUI->ScreenBlink(FColor::Orange);
		}
		else {
			playerUI->ScreenBlink(FColor::White);
		}
	}
}

void APhotoPlayer::FlashInput() {
	Flash();
}

void APhotoPlayer::JumpInput() {
	if(movementComponent->IsOnGround())
		movementComponent->SetVelocity((movementComponent->GetVelocityXY() * 1.25f) + (GetActorUpVector() * 15.0f));
}

void APhotoPlayer::LockInput() {
	if (lockOnNPC->IsValidLowLevel()) {
		lockOnNPC = nullptr;
	}
	else {
		lockOnNPC = targetNPC;
	}
}

void APhotoPlayer::OnOverlap(class UPrimitiveComponent* MainActor, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	if (OtherComp->GetAttachParent()->IsA(UHitbox::StaticClass())) {
		UHitbox* touchedHitbox = Cast<UHitbox, USceneComponent>(OtherComp->GetAttachParent());
		if (touchedHitbox->isHitting ==  true && touchedHitbox->appliedHit == false) {
			movementComponent->SetVelocity(movementComponent->GetVelocity()/1.25f);
			movementComponent->AddVelocity((GetActorUpVector() * 10.0f) + (GetActorForwardVector() * -10.0f));
			touchedHitbox->appliedHit = true;
			health -= 25.0f;
			flashCooldown = -flashCooldownTime;
			playerUI->ScreenBlink(FColor::Red);
		}
	}
}

float APhotoPlayer::GetHealth() {
	return health;
}

float APhotoPlayer::GetFlashCooldown() {
	return flashCooldown;
}

float APhotoPlayer::GetPhotoCooldown() {
	return photoCooldown;
}

TArray<ANPC*> APhotoPlayer::GetNPCsInView() {
	TArray<ANPC*> npcsInView;
	for (TActorIterator<ANPC> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ANPC* creature = *ActorItr;
		if(creature->WasRecentlyRendered(0.2f))
			npcsInView.Add(creature);
	}
	return npcsInView;
}